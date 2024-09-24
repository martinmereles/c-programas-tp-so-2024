#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <readline/readline.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <semaphore.h>


typedef enum {
    NEW,
    READY,
    EXEC,
    BLOCKED,
    EXIT
} T_ESTADO;

typedef struct {
    int pid;
    t_list* tids;
    t_list* mutex;
    T_ESTADO estado;
} t_pcb;

typedef struct {
    int tid;
    int ppid;
    int prioridad;
    T_ESTADO estado;
} t_tcb;

typedef struct
{
    uint32_t PC;
    uint32_t AX;
    uint32_t BX;
    uint32_t CX;
    uint32_t DX;
    uint32_t EX;
    uint32_t FX;
    uint32_t GX;
    uint32_t HX;
    uint32_t BASE;
    uint32_t LIMITE;
}t_contexto;

typedef struct {
    char* nombre;
    int valor;
    int pid_asignado;
    int tid_asignado;
    t_queue* bloqueados; 
}t_mutex;

typedef struct {
    int pid;
    int tid;
} t_proceso_hilo;


#endif