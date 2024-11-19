#include <stdio.h>
#include "paciente.h"
#include "funciones_utils.h"
#include "funciones_main.h"

int main(int argc, char *argv[])
{
    int opc;
    do
    {
        printf("\n\n\tMenu\n");
        printf("1.- Alta de paciente.\n2.- Busqueda o edicion de paciente.\n3.- Listado de pacientes.\n");
        printf("4.- Baja de pacientes.\n5.- Salir.\nIngrese la opcion a realizar:");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            alta_paciente();
            break;
        case 2:
            busqueda_y_edicion();
            break;
        case 3:
            imprimir_pacientes();
            break;
        case 4:
            baja_paciente();
            break;
        case 5:
            printf("Salida con exito!\n");
            break;
        default:
            printf("Opción no válida\n");
            break;
        }

    } while (opc != 5);

    return 0;
}
