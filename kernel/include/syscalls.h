#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

/*------------------------LIBRERIAS/INCLUDES------------------------*/
#include <utils/client-server.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <utils/estructuras.h>
#include <commons/collections/list.h>
#include <semaphore.h>
#include <commons/string.h>
#include <../include/auxiliares_kernel.h>

/*------------------------VARIABLES------------------------*/
extern t_log *logger;
extern t_config *config;
extern char *algoritmo_planificacion;
extern int quantum;
extern int socket_cpu_dispatch;
extern int socket_cpu_interrupt;
extern int socket_memoria;
extern t_list *QUEUE_NEW;
extern t_list *QUEUE_READY;
extern t_list *QUEUE_EXEC;
extern t_list *QUEUE_BLOCKED;
extern t_list *QUEUE_EXIT;
extern t_list *PCB_EN_CICLO;
extern t_list *TCB_BLOQUEADOS;
extern int contador_pid;
extern sem_t sem_largo_plazo;
extern sem_t sem_corto_plazo;
extern sem_t sem_contador_ready;
extern sem_t sem_mutex_colas;

/*------------------------DECLARACIONES------------------------*/
void sys_process_create(char *archivo, int tamanio, int prioridad, int pid, int tid);
void sys_process_exit(int pid, int tid);
void sys_thread_create(char *archivo_ps, int prioridad, int ppid, int tid);
void sys_thread_join(int tid_join, int ppid, int tid);
void sys_thread_cancel(int tid_cancel, int ppid, int tid);
void sys_thread_exit(int pid, int tid);
void sys_mutex_create(char *nombre, int pid, int tid);
void sys_mutex_lock(char *nombre, int pid, int tid);
void sys_mutex_unlock(char *nombre, int pid, int tid);
void sys_dump_memory(int pid, int tid);
void sys_io(int tiempo, int pid, int tid);
bool es_mutex_buscado(char *nombre, void *elemento);
void asignar_a_ready(t_tcb *tcb_a_asignar);
void atender_io(char *mensaje);

#endif