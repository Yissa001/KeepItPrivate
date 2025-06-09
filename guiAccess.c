//Esta es el inicio de mi proyecto de crear una app de terminal para guardar contraseñas de manera segura
//Primero crearemos una una interfaz de usuario 

#include <stdio.h> //para outputs and inputs
#include <string.h> //para cadena de caracteres 
#include <stdlib.h> //para utilizar la funcion exit()

int main()
{
    char user[31], passwd[31];
    int choice1, choice2;

    printf("Bienvenido a KeepItPrivate.\n");
    printf("\nPulse ""ENTER"" para continuar...\n");

    getchar(); //Aguarda que el usuario presione enter


    do
    {
        
        printf("¿Que deseas hacer?: (Selecciona un numero)\n");
        printf("1-) Iniciar sesión.\n");
        printf("2-) Crear nuevo usuario.\n");
        printf("3-) Exit\n");
        printf("\nIntroduce tu elección: ");
        scanf(" %d", &choice1);

        switch (choice1)
        {
            case(1):
            {
                printf("\nInicio de sesión.\n");
                printf("\nIntroduce tu usuario: ");
                getchar();
                fgets(user, sizeof(user), stdin);
                getchar();
                printf("\nAhora selecciona una contraseña: ");
                fgets(passwd, sizeof(passwd), stdin);

                if ((user == user)&&(passwd==passwd))
                {
                    printf("Acceso concedido.\n");
                }
                else
                {
                    printf("Contraseña o usuario incorrecto\n")
                }
                break;
            }

            case(2):
            {
            printf("Crear usuario.");
            printf("Introduce nombre del usuario: ");
            fgets(user, sizeof(user), stdin);
            break;
            }

            case(3):
                exit(1);
        }
    }
    while (choice1!=3);

    return (0);
}