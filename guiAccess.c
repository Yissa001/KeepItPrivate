//Esta es el inicio de mi proyecto de crear una app de terminal para guardar contraseñas de manera segura
//Primero crearemos una una interfaz de usuario 

#include <stdio.h> //para outputs and inputs
#include <string.h> //para cadena de caracteres 
#include <stdlib.h> //para utilizar la funcion exit()
#include <ctype.h> //para utilizar isdigit
#include <openssl/sha.h>
#include <openssl/rand.h>
#define FILE_NAME "usuarios.dat" //archivo para guardar usuarios y contraseñas 
#define MAX_USER 30
#define MAX_PASS 100
#define SALT_SIZE 16 // Tamaño del Slat
#define HASH_SIZE SHA512_DIGEST_LENGTH // Sha512 que produce 64-byte hashes
				       //
//Limpia el buffer/salto de linea que genera fgets o scanf
void limpiarSalto(char *cadena){
    cadena [strcspn(cadena, "\n")]= '\0';
}
//Verifica que haya al menos 2 numeros en la contraseña 
int verDosNros(const char *contraseña) {
    int contador= 0;
    for (int i = 0; contraseña[i] != '\0'; i++)
    {
        if (isdigit(contraseña[i]))
        {
            contador++;
            if (contador>=2)
            {
                return 1;
            }
        }
    }
    return 0;
}

void generarSalt(unsigned char *salt) {  //Genera salt único
	if (!RAND_bytes(salt, SALT_SIZE)) {
		printf("Error generando slat.\n");
		exit(1);
	}
}

void generarHash(const char *contraseña, const unsigned char *salt, unsigned char *hash) {
	unsigned char saltedPass[MAX_PASS + SALT_SIZE];

	//Concatenar contraseña con la salt
	strcpy((char *)saltedPass, contraseña);
	memcpy(saltedPass + strlen(contraseña), salt, SALT_SIZE);

	//Generar hash SHA512 
	SHA512(saltedPass, strlen(contraseña) + SALT_SIZE, hash);
}


void guardarUsuario(const char *user, const char *passwd) {
	FILE *fp =fopen(FILE_NAME, "wb"); //Abre el archivo en modo de escritura binaria
	if (fp == NULL) {
		printf("Error al crear el archivo.\n");
		exit(1);
	}

	unsigned char salt(SALT_SIZE);
	unsigned char hash(HASH_SIZE);
	
	//Generar el salt y el Hash 
	generarSalt(salt);
	generarHash(hash);

	//Escribe el usuario y contraseña en el archivo (salt y hash no la contraseña en texto plano)
	fwrite(user, sizeof(char), MAX_USER, fp);
	fwrite(salt, sizeof(unsigned char), SALT_SIZE, fp);
	fwrite(hash, sizeof(unsigned char), HASH_SIZE, fp);

	fclose(fp); //Cierra el archivo 
	printf("Usuario registrado exitosamente!\n");
}

void leerUsuario(char *user, unsigned char *salt, unsigned char *hash) {
	FILE *fp = fopen(FILE_NAME, "rb"); //Abre el archivo en modo lectura binaria 
	if (fp == NULL) {
		return 0;
	}

	//Leer usuario y contraseña desde el archivo 
	fread(user, sizeof(char), MAX_USER, fp);
	fread(salt, sizeof(unsigned char), SALT_SIZE, fp);
	fread(hash, sizeof(unsigend char), HASH_SIZE, fp);

	fclose(fp);
	return 1;
}


int main()

{
    char user[MAX_USER + 1] = "";
    char inputUser[MAX_USER + 1];
    char inputPass[MAX_PASS + 1];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];
    int choice;

    printf("Bienvenido a KeepItPrivate.\n");
    printf("\nPulse ""ENTER"" para continuar...\n");

    getchar(); //Aguarda que el usuario presione enter
	int usuarioExistente = leerUsuario(user, salt, storedHash);
	
    while(1)
    {
        printf("Elige un número:\n");
        printf("1-) Iniciar sesión.\n");
        printf("2-) Crear nuevo usuario.\n");
        printf("3-) Salir.\n");
	printf("Opción");
        scanf(" %d", &choice);
        getchar(); //Limpia buffer 

        switch (choice){
            case(1):
            {
		    if(!usuarioExistente) {
			    printf("No hay usuarios registrados. Crea uno primero.\n");
			    break;
			}

                printf("Inicio de sesión\n");
                printf("Usuario: ");
                fgets(inputUser, sizeof(inputUser), stdin);
                limpiarSalto(inputUser);

                printf("Contraseña: ");
                fgets(inputPass, sizeof(inputPass), stdin);
                limpiarSalto(inputPass);

                if ((strcmp(user1, user)==0)&&(strcmp(passwd, passwd1)==0))
                {
                    printf("Acceso concedido.\n");
                }
                else
                {
                    printf("Usuario o contraseña incorrecta. Intente de nuevo.\n");
                }
                break;
            }
            case(2):
            {
		    if (user[0] != '\0'){
			    printf("Ya existe un usuario registrado. Solo se permite uno.\n");
			    break;
			}

                //Bucle para verificar que el largor del nombre de usuario no supere los 30 caracteres.
                while(1)
                {
                    printf("Crea un nombre de usuario: ");
                    fgets(user, sizeof(user), stdin);
                    limpiarSalto(user);

                    if(strlen(user)>=MAX_USER)
                    {
                        printf("\nEl nombre del usuario no puede ser mayor a 30 caracteres.\n");
                        printf("Inténtelo de nuevo.\n");
                    }
                    else
                    {
                        break;
                    }
                }
                while(1)
                {
                    printf("No se preocupe si no puede visualizar lo que escribe, realmente esta escribiendo tenga cuidado.\n");
                    printf("Cree su contraseña: ");
                    fgets(passwd, sizeof(passwd), stdin);
                    limpiarSalto(passwd);

                    if (strlen(passwd)< 14) //Verifica que la contraseña tenga al menos 14 digitos.
                    {
                        printf("\nSu contraseña es demasiado corta.\n");
                        printf("Intente de nuevo.\n");
                    }
                    else if (!verDosNros(passwd)) //verifica que la contraseña contenga al menos 2 numeros.
                    {
                        printf("\nSu contraseña debe de tener al menos 2 números.\n");
                        printf("Intente de nuevo\n");
                    }
                    else
                    {
                        break;
                    }
                }
		printf("DEBUG: Guardando usuario en archivo...\n");
		guardarUsuario(user, passwd); //Guarda solo cuando la contraseña es valida
                break;
            }
            case(3):
            {
                exit(0);
            }
        }
    }
    return (0);

}
