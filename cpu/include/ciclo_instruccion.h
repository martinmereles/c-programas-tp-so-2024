#ifndef CICLO_INSTRUCCION_H_
#define CICLO_INSTRUCCION_H_

/*------------------------LIBRERIAS------------------------*/
#include <commons/string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern int pid;
extern int tid;
extern uint32_t PC;

/*------------------------DECLARACIONES------------------------*/
void fetch(int socket_cliente_memoria);
void decode(int socket_cliente_memoria);
void execute(int socket_cliente_memoria);
void check_interrupt(int socket_cliente_memoria);

#endif