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

extern char* algoritmo_planificacion;
extern int quantum;

extern int socket_cpu_dispatch;
extern int socket_cpu_interrupt;
extern int socket_memoria;
extern t_list* QUEUE_NEW;
extern t_list* QUEUE_READY;
extern t_list* QUEUE_EXEC;
extern t_list* QUEUE_BLOCKED;
extern t_list* QUEUE_EXIT;
extern t_list* PCB_EN_CICLO;
extern int contador_pid;

extern sem_t sem_largo_plazo;
extern sem_t sem_corto_plazo;
extern sem_t sem_contador_ready;
extern sem_t sem_mutex_colas;

void crear_proceso (char* archivo, int tamanio, int prioridad);
void finalizar_proceso (t_pcb* pcb;);
bool es_pcb_buscado(int pid_buscado, void *elemento);
void planificador_largo_plazo ();
t_tcb* crear_hilo (int prioridad, int ppid, int tid);
void finalizar_hilo (int pid, int tid, t_list* cola);
bool es_tcb_buscado(int pid_buscado, int tid_buscado, void *elemento);

void ejecutar_fifo(socket_cpu_dispatch);
void ejecutar_prioridades(socket_cpu_dispatch, socket_cpu_interrupt);
void ejecutar_cmn(socket_cpu_dispatch, socket_cpu_interrupt);

void dispatcher(int tid, int pid, int socket_cpu_dispatch);
void aviso_quantum(char* mensaje);

int get_index (int prioridad);

char *recibir_desde_memoria(int socket_cliente);
char *recibir_desde_cpu(int socket_cliente);



#endif