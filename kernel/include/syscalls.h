#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

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


void sys_process_create (char* archivo, int tamanio, int prioridad);
void sys_process_exit (int tid);
void sys_thread_create(char* archivo_ps, int tid);
void sys_thread_join (int tid);
void sys_thread_cancel (int tid);
void sys_thread_exit (int tid);
void sys_mutex_create ();
void sys_mutex_lock ();
void sys_mutex_unlock ();

#endif