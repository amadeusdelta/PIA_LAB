#ifndef FUNCIONES_UTILS_H
#define FUNCIONES_UTILS_H

#include "paciente.h"
#include <stdio.h>

int obtener_num_pacientes();
int escribir_paciente_nuevo(struct Paciente paciente, FILE *f);
void imprimir_paciente(struct Paciente paciente);
struct Paciente obtener_paciente_nuevo();
struct Paciente *leer_pacientes();

#endif
