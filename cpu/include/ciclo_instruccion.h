#ifndef CICLO_INSTRUCCION_H_
#define CICLO_INSTRUCCION_H_

/*------------------------LIBRERIAS------------------------*/
#include <commons/string.h>
#include <commons/log.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*------------------------VARIABLES------------------------*/
extern int socket_memoria;
extern int pid;
extern int tid;
extern uint32_t PC;
extern uint32_t BASE;
extern char* instruccion_exec;
extern t_log* logger;

/*------------------------DECLARACIONES------------------------*/
void fetch();
void decode();
void execute();
void check_interrupt();

#endif