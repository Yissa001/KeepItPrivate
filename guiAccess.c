//Esta es el inicio de mi proyecto de crear una app de terminal para guardar contraseñas de manera segura
 

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
		printf("Error generando salt.\n");
		exit(1);
	}
}

void generarHash(const char *contraseña, const unsigned char *salt, unsigned char *hash) {
	unsigned char buffer[MAX_PASS + SALT_SIZE];
	size_t pass_len = strlen(contraseña);
	if (pass_len > MAX_PASS) {
		printf("Error: contraseña demasiado larga.\n");
		exit(1);
	}

	//Concatenar contraseña con la salt
	memcpy(buffer, contraseña, pass_len);
	memcpy(buffer + pass_len, salt, SALT_SIZE);

	//Generar hash SHA512 
	SHA512(buffer, pass_len + SALT_SIZE, hash);
}


void guardarUsuario(const char *user, const char *passwd) {
	FILE *fp = fopen(FILE_NAME, "wb"); //Abre el archivo en modo de escritura binaria
	if (fp == NULL) {
		printf("Error al crear el archivo.\n");
		exit(1);
	}

	unsigned char salt[SALT_SIZE];
	unsigned char hash[HASH_SIZE];
	
	//Generar el salt y el Hash 
	generarSalt(salt);
	generarHash(passwd, salt, hash);

	char user_fixed[MAX_USER + 1];
	memset(user_fixed, 0, sizeof user_fixed);
	strncpy(user_fixed, user, MAX_USER);


	//Escribe el usuario y contraseña en el archivo (salt y hash no la contraseña en texto plano)
	fwrite(user_fixed, 1, MAX_USER + 1, fp);
	fwrite(salt, 1, SALT_SIZE, fp);
	fwrite(hash, 1, HASH_SIZE, fp);

	fclose(fp); //Cierra el archivo 
	printf("Usuario registrado exitosamente!\n");
}


int leerUsuario(char *user, unsigned char *salt, unsigned char *hash) {
	FILE *fp = fopen(FILE_NAME, "rb"); //Abre el archivo en modo lectura binaria 
	if (fp == NULL) {
		return 0;
	}

	//Leer usuario y contraseña desde el archivo 
	char user_fixed[MAX_USER + 1];
	memset(user_fixed, 0, sizeof user_fixed);
	size_t nread = fread(user_fixed, sizeof(char), MAX_USER + 1, fp);
	if (nread < MAX_USER + 1) {
		fclose(fp);
		return 0;
	}
	//Copia el buffer
	strcpy(user, user_fixed);

	if (fread(salt, sizeof(unsigned char), SALT_SIZE, fp) != SALT_SIZE) {
		fclose(fp);
		return 0;
	}
	if (fread(hash, sizeof(unsigned char), HASH_SIZE, fp) != HASH_SIZE) {
		fclose(fp);
		return 0;
	}

	fclose(fp);
	return 1;
}


int main(void)

{
    char user[MAX_USER + 1] = {0};
    char inputUser[MAX_USER + 1];
    char inputPass[MAX_PASS + 1];
    unsigned char salt[SALT_SIZE] = {0};
    unsigned char storedHash[HASH_SIZE] = {0};
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
	printf("Opción: ");
        if (scanf(" %d", &choice) != 1) {
		printf("Entrada inválida.\n");
		int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
		continue;
	}
	int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}


        switch (choice){
            case(1):
            {
		    if(!usuarioExistente) {
			    printf("No hay usuarios registrados. Crea uno primero.\n");
			    break;
			}

                printf("Inicio de sesión\n");
                printf("Usuario: ");
                if (!fgets (inputUser, sizeof(inputUser), stdin)) break;
                limpiarSalto(inputUser);

                printf("Contraseña: ");
                if (!fgets(inputPass, sizeof(inputPass), stdin)) break;
                limpiarSalto(inputPass);


		//Verificacion de usuario.
                if (strcmp(inputUser, user) != 0){
                    printf("Usuario incorrecto.\n");
		    break;
                }
                
		//Verificador de contraseña 
		unsigned char inputHash[HASH_SIZE];
		generarHash(inputPass, salt, inputHash);

		if (memcmp(inputHash, storedHash, HASH_SIZE) == 0) {
			printf("\nAcceso concedido. ¡Bienvenido %s!\n", user);
			}
		else {
			printf("Contraseña incorrecta.\n");
		}
		break;
	}

            case(2): //Creación de usuario unico
            {
		    if (usuarioExistente){
			    printf("Ya existe un usuario registrado. Solo se permite uno.\n");
			    break;
			}

                //Bucle para verificar que el largor del nombre de usuario no supere los 30 caracteres.
                while(1)
                {
                    printf("Crear nuevo usuario\n");
		    printf("Nombre de usuario (max %d caracteres): ", MAX_USER);
                    if (!fgets(user, sizeof(user), stdin)) break;
                    limpiarSalto(user);

                    size_t len = strlen(user);
		    if (len == 0) {
			    printf("\nEl nombre del usuario no puede estar vacío.\n");
			}
		    else if (len > MAX_USER) {
			    printf("El nombre es demasiado largo.\n");
			}
		    else {
			    break;
			}
                }

		//Validar contraseña 
                while(1)
                {
                    printf("Requisitos de contraseña:");
                    printf("\n- Mínimo 14 caracteres");
		    printf("\n- Al menos debe contener 2 números\n");
		    printf("Contraseña: ");
                    if (!fgets(inputPass, sizeof(inputPass), stdin)) break;
                    limpiarSalto(inputPass);


                    if (strlen(inputPass)< 14) //Verifica que la contraseña tenga al menos 14 digitos.
                    {
                        printf("\nLa contraseña es demasiado corta.\n");
                    }
                    else if (!verDosNros(inputPass)) //verifica que la contraseña contenga al menos 2 numeros.
                    {
                        printf("\nLa contraseña debe contener al menos 2 números.\n");
                    }
                    else
                    {
                        break;
                    }
                }

		printf("DEBUG: Guardando usuario en archivo...\n");
		guardarUsuario(user, inputPass); //Guarda solo cuando la contraseña es valida
		usuarioExistente = 1;
		printf("Usuario creado exitosamente!\n");
                break;

            }
            
	    case(3):
            
		printf("Saliendo...\n");
                return 0;
            
	    	default: 
			     printf("Opción no válida.\n");
        }
    }
    //return (0);

}
