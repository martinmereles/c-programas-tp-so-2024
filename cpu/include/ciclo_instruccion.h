#ifndef CICLO_INSTRUCCION_H_
#define CICLO_INSTRUCCION_H_

/*------------------------LIBRERIAS------------------------*/
#include <utils/client-server.h>
#include <../include/auxiliares_cpu.h>
#include <../include/mmu.h>
#include <commons/string.h>
#include <commons/log.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

/*------------------------VARIABLES------------------------*/
extern int socket_memoria;
extern int socket_kernel_dispatch;
extern int pid;
extern int tid;
extern bool se_ejecuto_syscall;
extern uint32_t PC;
extern uint32_t BASE;
extern char* instruccion_exec;
extern t_log* logger;
extern t_list* interrupciones;
extern sem_t sem_execute;
/*------------------------DECLARACIONES------------------------*/
void fetch();
void decode();
void execute();
void check_interrupt();

#endif