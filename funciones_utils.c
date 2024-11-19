#include "funciones_utils.h"
#include "paciente.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Define la variable global null_paciente
struct Paciente null_paciente = {"", "", "", -1, '\0', -1, -1, -1};

/*Funciones generales usadas por las funciones principales*/

// Obtiene el numero de pacientes en registros.txt desde extra.txt
int obtener_num_pacientes()
{
    FILE *f;
    int num_pacientes;
    f = fopen("extra.txt", "r+");
    if (f == NULL)
    {
        f = fopen("extra.txt", "w+");
        if (f == NULL)
        {
            printf("Error abriendo extra.txt\n");
            return 0;
        }
        fprintf(f, "0\n");
        num_pacientes = 0;
    }
    else if (fgetc(f) == EOF)
    {
        fprintf(f, "0\n");
        num_pacientes = 0;
    }
    else
    {
        rewind(f);
        fscanf(f, "%d\n", &num_pacientes);
    }
    fclose(f);
    return num_pacientes;
}

// Imprime el paciente a pantalla
void imprimir_paciente(struct Paciente paciente)
{

    if (paciente.opc == 1)
    {
        printf("Consulta externa\n");
    }
    else if (paciente.opc == 2)
    {
        printf("Consulta de emergencia\n");
    }

    printf("Numero de registro: %d\n", paciente.num_registro);
    printf("Nombre: %s\n", paciente.nombre);
    printf("Direccion: %s\n", paciente.direccion);
    printf("Sintomas: %s\n", paciente.sintomas);

    if (paciente.edad > 1000)
    {
        printf("La edad del paciente es: %d months\n", paciente.edad - 1000);
    }
    else
    {
        printf("La edad del paciente es: %d years\n", paciente.edad);
    }

    printf("Genero: %c\n", paciente.genero);
    printf("Consultorio: %d\n", paciente.consultorio);
}

// leer pacientes de archivo
struct Paciente *leer_pacientes()
{
    FILE *f;
    int num_pacientes = obtener_num_pacientes();
    struct Paciente *pacientes = malloc(num_pacientes * sizeof(struct Paciente));
    if (pacientes == NULL)
    {
        printf("Error de asignacion de memoria\n");
        return &null_paciente;
    }

    if ((f = fopen("registros.txt", "r")) == NULL)
    {
        printf("Ha habido un problema al leer el archivo\n");
        free(pacientes);
        return &null_paciente;
    }

    int i = 0;
    while (i < num_pacientes && fscanf(f, "%d|%[^|]|%[^|]|%d|%c|%[^|]|%d|%d\n",
                                       &pacientes[i].opc,
                                       pacientes[i].nombre,
                                       pacientes[i].direccion,
                                       &pacientes[i].edad,
                                       &pacientes[i].genero,
                                       pacientes[i].sintomas,
                                       &pacientes[i].consultorio,
                                       &pacientes[i].num_registro) == 8)
    {
        i++;
    }

    fclose(f);
    return pacientes;
}

/*Llenado de estructura*/
struct Paciente obtener_paciente_nuevo()
{
    int opc;
    FILE *f;
    struct Paciente paciente;
    srand(time(NULL));

    printf("Tipo de servicio:\n1.-Consulta externa.\n2.-Consulta de emergencia.\n");
    do
    {
        printf("Ingrese el tipo de servicio: \n");
        scanf("%d", &opc);
        getchar();
        if (opc != 1 && opc != 2)
            printf("Opcion no valida\n");
    } while (opc != 1 && opc != 2);

    paciente.opc = opc;

    printf("Ingrese el nombre del paciente:\n");
    fgets(paciente.nombre, sizeof(paciente.nombre), stdin);
    paciente.nombre[strcspn(paciente.nombre, "\n")] = 0;

    printf("Ingrese la direccion del paciente:\n");
    fgets(paciente.direccion, sizeof(paciente.direccion), stdin);
    paciente.direccion[strcspn(paciente.direccion, "\n")] = 0;

    int op;
    printf("Es el paciente recien nacido?\n");
    printf("1.-Si.\n2.-No.\n");

    do
    {
        printf("Ingrese la opcion:\n");
        scanf("%d", &op);
        getchar();
        if (op != 1 && op != 2)
            printf("Opcion no valida\n");
    } while (op != 1 && op != 2);

    if (op == 1)
    {
        do
        {
            printf("Ingrese la edad del paciente en meses:\n");
            scanf("%d", &paciente.edad);
        } while (!(paciente.edad <= 12 && paciente.edad >= 1));

        paciente.edad += 1000;
    }
    if (op == 2)
    {
        do
        {
            printf("Ingrese la edad del paciente en years:\n");
            scanf("%d", &paciente.edad);
        } while (paciente.edad < 1);
    }

    do
    {
        printf("Ingrese el genero, femenino (F) o masculino (M): ");
        scanf(" %c", &paciente.genero);
        getchar();
    } while (paciente.genero != 'F' && paciente.genero != 'M');

    printf("Ingrese la descripcion de los sintomas:\n");
    fgets(paciente.sintomas, sizeof(paciente.sintomas), stdin);
    paciente.sintomas[strcspn(paciente.sintomas, "\n")] = 0;

    do
    {
        printf("Ingrese el numero de consultorio:\n");
        scanf("%d", &paciente.consultorio);
        getchar();
    } while (paciente.consultorio < 0);

    paciente.num_registro = obtener_num_pacientes() + 1;

    return paciente;
}

/*Copia estructura en archivo*/
int escribir_paciente_nuevo(struct Paciente paciente, FILE *f)
{
    FILE *extra;

    int num_pacientes = obtener_num_pacientes();

    // Se actualiza el numero de pacientes en extra
    if ((extra = fopen("extra.txt", "w")) == NULL)
    {
        printf("Hubo un error al abrir el archivo");
        return 0;
    }

    fprintf(extra, "%d\n", ++num_pacientes);

    fclose(extra);

    fseek(f, 0, SEEK_END);

    fprintf(f, "%d|", paciente.opc);

    fprintf(f, "%s|", paciente.nombre);

    fprintf(f, "%s|", paciente.direccion);

    fprintf(f, "%d|", paciente.edad);

    fprintf(f, "%c|", paciente.genero);

    fprintf(f, "%s|", paciente.sintomas);

    fprintf(f, "%d|", paciente.consultorio);

    fprintf(f, "%d\n", paciente.num_registro);

    return 0;
}
