#ifndef SYSCALLS_CPU_H
#define SYSCALLS_CPU_H

#include <../include/auxiliares_cpu.h>

extern int socket_kernel_dispatch;
extern int socket_memoria;
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


void process_create(char * arch_instrucciones, char *tamanio, char *prioridad_tid);
void process_exit();
void thread_create(char * arch_instrucciones, char* prioridad);
void thread_join(char* tid);
void thread_cancel(char* tid);
void thread_exit();
void mutex_create(char* recurso);
void mutex_lock(char* recurso);
void mutex_unlock(char* recurso);
void dump_memory();
void io(char* tiempo);

#endif