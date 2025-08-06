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

void guardarUsuario(const char *user, const char *passwd) {
	FILE *fp =fopen(FILE_NAME, "wb"); //Abre el archivo en modo de escritura binaria
	if (fp == NULL) {
		printf("Error al crear el archivo.\n");
		exit(1);
	}
	//Escribe el usuario y contraseña en el archivo
	fwrite(user, sizeof(char), MAX_USER, fp);
	fwrite(passwd, sizeof(char), MAX_PASS, fp);
	fclose(fp); //Cierra el archivo 
	printf("Usuario registrado exitosamente!\n");
}

void leerUsuario(char *user, char *passwd) {
	FILE *fp = fopen(FILE_NAME, "rb"); //Abre el archivo en modo lectura binaria 
	if (fp == NULL) {
		user[0] = '\0';
		passwd[0] = '\0';
		return;
	}
	//Leer usuario y contraseña desde el archivo 
	fread(user, sizeof(char), MAX_USER, fp);
	fread(passwd, sizeof(char), MAX_PASS, fp);
	fclose(fp);
}


int main()

{
    char user1[MAX_USER + 1], passwd1[MAX_PASS + 1];
    int choice1;

    printf("Bienvenido a KeepItPrivate.\n");
    printf("\nPulse ""ENTER"" para continuar...\n");

    getchar(); //Aguarda que el usuario presione enter
	char user[MAX_USER + 1] = ""; //+1 para el caracter nulo
	char passwd[MAX_PASS + 1] = "";
	leerUsuario(user, passwd); //Carga datos desde el archivo
	
    while(1)
    {
        printf("Elige un número:\n");
        printf("1-) Iniciar sesión.\n");
        printf("2-) Crear nuevo usuario.\n");
        printf("3-) Cerrar aplicación.\n");
        scanf(" %d", &choice1);
        getchar();

        switch (choice1){
            case(1):
            {
                printf("Inicio de sesión\n");
                printf("Nombre de usuario: ");
                fgets(user1, sizeof(user1), stdin);
                limpiarSalto(user1);

                printf("\nIntroduce la contraseña del usuario %s:", user1);
                fgets(passwd1, sizeof(passwd1), stdin);
                limpiarSalto(passwd1);

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
