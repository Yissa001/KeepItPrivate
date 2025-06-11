//Esta es el inicio de mi proyecto de crear una app de terminal para guardar contraseñas de manera segura
//Primero crearemos una una interfaz de usuario 

#include <stdio.h> //para outputs and inputs
#include <string.h> //para cadena de caracteres 
#include <stdlib.h> //para utilizar la funcion exit()
#include <ctype.h> //para utilizar isdigit
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

int main()

{
    FILE *fp;
    char user[31], passwd[101], user1[31], passwd1[101];
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
                //Bucle para verificar que el largor del nombre de usuario no supere los 30 caracteres.
                while(1)
                {
                    printf("Crea un nombre de usuario: ");
                    fgets(user, sizeof(user), stdin);
                    limpiarSalto(user);

                    if(strlen(user)>30)
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