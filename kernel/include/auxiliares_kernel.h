#ifndef _AUXILIARES_KERNEL_H_
#define _AUXILIARES_KERNEL_H_

#include <utils/client-server.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <utils/estructuras.h>
#include <commons/collections/list.h>
#include <semaphore.h>
#include <commons/string.h>



extern t_log* logger;
extern t_config* config;
extern int socket_cpu_dispatch;
extern int socket_cpu_interrupt;
extern int socket_memoria;
extern t_list* QUEUE_NEW;
extern t_list* QUEUE_READY;
extern t_list* QUEUE_EXEC;
extern t_list* QUEUE_BLOCKED;
extern t_list* QUEUE_EXIT;
extern int contador_pid;

extern sem_t sem_largo_plazo;

void crear_proceso (char* archivo, int tamanio, int prioridad);
void finalizar_proceso (t_pcb* pcb;);
bool es_pcb_buscado(int pid_buscado, void *elemento);


#endif