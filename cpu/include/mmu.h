#ifndef MMU_H
#define MMU_H

/*------------------------LIBRERIAS------------------------*/
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
/*------------------------VARIABLES------------------------*/
extern int socket_kernel_dispatch;
extern sem_t sem_execute;
extern int pid;
extern int tid;
extern uint32_t PC;
extern uint32_t AX;
extern uint32_t BX;
extern uint32_t CX;
extern uint32_t DX;
extern uint32_t EX;
extern uint32_t FX;
extern uint32_t GX;
extern uint32_t HX;
extern uint32_t BASE;
extern uint32_t LIMITE;

extern int direccion_fisica;

/*------------------------DECLARACIONES------------------------*/
void validar_direccion(int direccion);
int obtener_direccion_fisica(int direccion_logica);

#endif