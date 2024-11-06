#ifndef INSTRUCCIONES_CPU_H
#define INSTRUCCIONES_CPU_H

/*------------------------LIBRERIAS------------------------*/
#include <../include/auxiliares_cpu.h>
#include <../include/syscalls_cpu.h>
#include <../include/mmu.h>

/*------------------------VARIABLES------------------------*/
extern int socket_memoria;
extern int socket_kernel_dispatch;
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

/*------------------------DECLARACIONES------------------------*/
void set(char *registro, char *valor);
void read_mem(char* registro_datos, char* registro_direccion);
void write_mem(char* registro_direccion, char* registro_datos);
void sum(char *registro_destino, char *registro_origen);
void sub(char *registro_destino, char *registro_origen);
void jnz(char *registro, char *instruccion);
void log(char* registro);
void ejecutarSentencia(int socket_cliente_memoria);

#endif