// paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

struct Paciente
{
    char nombre[40];
    char direccion[120];
    char sintomas[255];
    int edad;
    char genero;
    int consultorio;
    int num_registro;
    int opc;
};

extern struct Paciente null_paciente;

#endif
