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


void process_create (char* archivo, int tamanio, int prioridad);
void process_exit (int tid);
void thread_create(char* archivo_ps, int tid);
void thread_join (int tid):
void thread_cancel (int tid);
void thread_exit (int tid);
void mutex_create ();
void mutex_lock ();
void mutex_unlock ();