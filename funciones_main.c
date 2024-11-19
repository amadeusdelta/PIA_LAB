#include "funciones_main.h"
#include "funciones_utils.h"
#include "paciente.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*
Funciones principales usadas en el switch del programa principal
*/

/*ALTA DE PACIENTES*/
void alta_paciente()
{
    printf("");
    struct Paciente paciente;
    FILE *f;
    if ((f = fopen("registros.txt", "a+")) == NULL)
    {
        printf("No se pudo abrir el archivo");
        return;
    }

    paciente = obtener_paciente_nuevo();
    escribir_paciente_nuevo(paciente, f);
    fclose(f);
}

/*BUSQUEDA O EDICION DE PACIENTES*/
void busqueda_y_edicion()
{
    int opc1, opc2, flag = 0;
    int num_pacientes = obtener_num_pacientes();
    struct Paciente paciente;

    if (num_pacientes == 0)
    {
        printf("\nNo se encontraron pacientes\n\n");
        return;
    }

    struct Paciente *pacientes = leer_pacientes();
    if (pacientes == &null_paciente)
    {
        printf("No se pudieron leer los pacientes.\n");
        return;
    }
    do
    {
        printf("1) Edicion \n2) Busqueda\nOpcion: ");
        scanf("%d", &opc1);
        getchar();
        if (opc1 != 1 && opc1 != 2)
            printf("Opcion no valida");
    } while (opc1 != 1 && opc1 != 2);

    if (opc1 == 1)
    {
        FILE *f, *extra;
        int pos = -1;

        printf("1) Edicion por nombre\n2) Edicion por numero de registro\nOpcion: ");
        scanf("%d", &opc2);

        if (opc2 == 1)
        {
            char nombre[40];
            printf("Ingrese el nombre del paciente a buscar: ");
            getchar();
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = 0;
            int i;
            for (i = 0; i < num_pacientes; i++)
            {
                if (strcmp(pacientes[i].nombre, nombre) == 0)
                {
                    pos = i;
                    paciente = obtener_paciente_nuevo();
                    flag = 1;
                    break;
                }
            }
        }
        else if (opc2 == 2)
        {
            int num_registro;
            printf("Ingrese el numero de registro: ");
            scanf("%d", &num_registro);
            getchar();
            int i;
            for (i = 0; i < num_pacientes; i++)
            {
                if (pacientes[i].num_registro == num_registro)
                {
                    pos = i;
                    paciente = obtener_paciente_nuevo();
                    flag = 1;
                    break;
                }
            }
        }

        if (flag == 0)
        {
            printf("\nNo se pudo encontrar el paciente buscado\n\n");
            free(pacientes);
            return;
        }

        extra = fopen("extra.txt", "w");
        f = fopen("registros.txt", "w");
        if (f == NULL || extra == NULL)
        {
            printf("\nNo se pudieron abrir correctamente los archivos para edicion\n\n");
            free(pacientes);
            return;
        }

        fprintf(extra, "0\n");
        fclose(extra);
        int i;
        for (i = 0; i < num_pacientes; i++)
        {
            pacientes[i].num_registro = i + 1;
            if (i == pos)
            {
                paciente.num_registro = i + 1;
                escribir_paciente_nuevo(paciente, f);
            }
            else
            {
                escribir_paciente_nuevo(pacientes[i], f);
            }
        }

        fclose(f);
        free(pacientes);
    }
    else if (opc1 == 2)
    {
        printf("1) Busqueda por nombre\n2) Busqueda por numero de registro\nOpcion: ");
        scanf("%d", &opc2);
        getchar();

        if (opc2 == 1)
        {
            char nombre[40];
            printf("Ingrese el nombre del paciente a buscar: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = 0;
            int i;
            for (i = 0; i < num_pacientes; i++)
            {
                if (strcmp(pacientes[i].nombre, nombre) == 0)
                {
                    printf("\n==============================================\n\n");
                    imprimir_paciente(pacientes[i]);
                    printf("\n==============================================\n\n");
                    flag = 1;
                    break;
                }
            }
        }
        else if (opc2 == 2)
        {
            int num_registro;
            printf("Ingrese el numero de registro: ");
            scanf("%d", &num_registro);
            getchar();
            int i;
            for (i = 0; i < num_pacientes; i++)
            {
                if (pacientes[i].num_registro == num_registro)
                {
                    printf("\n==============================================\n\n");
                    imprimir_paciente(pacientes[i]);
                    printf("\n==============================================\n\n");
                    flag = 1;
                    break;
                }
            }
        }

        if (flag == 0)
        {
            printf("\nNo se pudo encontrar al paciente buscado\n\n");
        }

        free(pacientes);
    }
}

/*LISTADO DE PACIENTES*/
void imprimir_pacientes()
{
    int num_pacientes = obtener_num_pacientes();
    if (num_pacientes == 0)
    {
        printf("\nNo se encontraron pacientes\n\n");
        return;
    }

    struct Paciente *pacientes = leer_pacientes();
    if (pacientes == &null_paciente)
    {
        printf("No se pudieron leer los pacientes.\n");
        return;
    }

    printf("\n==============================================\n");
    printf("           Lista de Pacientes del Hospital      ");
    printf("\n==============================================\n\n");
    int i;
    for (i = 0; i < num_pacientes; i++)
    {
        imprimir_paciente(pacientes[i]);
        printf("\n==============================================\n\n");
    }

    printf("\n==============================================\n\n");
    free(pacientes);
}

/*BAJA DE PACIENTES*/
void baja_paciente()
{
    int num_pacientes = obtener_num_pacientes();
    struct Paciente *pacientes = leer_pacientes();

    FILE *f, *temporal;
    int opc, num, encontrado = 0;
    char nombre[40];

    if (num_pacientes == 0)
    {
        printf("\nNo se encontraron pacientes\n\n");
        return;
    }

    if ((f = fopen("registros.txt", "r")) == NULL)
    {
        printf("El archivo registros.txt no se pudo abrir.\n");
        return;
    }

    if ((temporal = fopen("temporal.txt", "w")) == NULL)
    {
        printf("El archivo temporal.txt no se pudo abrir.\n");
        fclose(f);
        return;
    }

    printf("1.- Baja del paciente por nombre.\n2.- Baja del paciente por numero de registro.\n");
    scanf("%d", &opc);
    getchar();

    if (opc == 1)
    {
        printf("Ingrese el nombre del paciente a buscar: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = 0;

        for (int i = 0; i < num_pacientes; i++)
        {
            if (strcmp(pacientes[i].nombre, nombre) != 0)
            {
                if (encontrado == 1)
                {
                    pacientes[i].num_registro = pacientes[i].num_registro - 1;
                }
                escribir_paciente_nuevo(pacientes[i], temporal);
            }
            else
            {
                encontrado = 1;
            }
        }
    }
    else if (opc == 2)
    {
        printf("Ingrese el numero de registro del paciente: ");
        scanf("%d", &num);

        for (int i = 0; i < num_pacientes; i++)
        {
            if (pacientes[i].num_registro != num)
            {
                if (encontrado == 1)
                {
                    pacientes[i].num_registro = pacientes[i].num_registro - 1;
                }
                // Este es el problema dentro del codigo
                escribir_paciente_nuevo(pacientes[i], temporal);
            }
            else
            {
                encontrado = 1;
            }
        }
    }

    free(pacientes);

    FILE *extra;

    if (!encontrado)
    {
        printf("El paciente no se encontro.\n");

        if ((extra = fopen("extra.txt", "r+")) == NULL)
        {
            printf("Hubo un error al abrir extra.txt, retornando.\n");
            fclose(f);
            fclose(temporal);
            remove("temporal.txt");
            return;
        }
        fprintf(extra, "%d\n", num_pacientes);
        fclose(f);
        fclose(extra);
        fclose(temporal);
        remove("temporal.txt");
        return;
    }

    // Se corrige el número de pacientes
    if ((extra = fopen("extra.txt", "r+")) == NULL)
    {
        printf("Hubo un error al abrir extra.txt, retornando.\n");
        fclose(f);
        fclose(temporal);
        remove("temporal.txt");
        return;
    }

    fprintf(extra, "%d\n", num_pacientes - 1);

    fclose(extra);
    fclose(f);
    fclose(temporal);

    remove("registros.txt");
    rename("temporal.txt", "registros.txt");

    printf("\nEl paciente fue dado de baja exitosamente.\n");
}
