//Esta es el inicio de mi proyecto de crear una app de terminal para guardar contraseñas de manera segura
//Primero crearemos una una interfaz de usuario 

#include <stdio.h> //para outputs and inputs
#include <string.h> //para cadena de caracteres 
#include <stdlib.h> //para utilizar la funcion exit()

void limpiarSalto(char *cadena){
    cadena [strcspn(cadena, "\n")]= '\0';
}

int main()

{
    char user[31], passwd[31], user1[31], passwd1[31];
    int choice1, choice2;

    printf("Bienvenido a KeepItPrivate.\n");
    printf("\nPulse ""ENTER"" para continuar...\n");

    getchar(); //Aguarda que el usuario presione enter

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
                    printf("Usuario o contraseña incorrecta. Intente de nuevo");
                }
                break;
            }
            case(2):
            {
                printf("Creación de usuario.\n");
                printf("Crea un usuario: ");
                fgets(user, sizeof(user), stdin);
                limpiarSalto(user);
                strcpy(user, user1);

                printf("\nCrea una contraseña. (Debe ser de 14 dígitos, poseer 4 números y un al menos un carácter especial.)\n");
                printf("No te preocupes si no ves lo que escribes, de esta forma esta diseñado.\n");
                printf("Contraseña: ");
                fgets(passwd, sizeof(passwd), stdin);
                limpiarSalto(passwd);
                strcpy(passwd, passwd1);

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