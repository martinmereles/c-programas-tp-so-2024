#ifndef _AUXILIARES_KERNEL_H_
#define _AUXILIARES_KERNEL_H_

/*------------------------LIBRERIAS/INCLUDES------------------------*/
#include <utils/client-server.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <utils/estructuras.h>
#include <commons/collections/list.h>
#include <semaphore.h>
#include <commons/string.h>

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
void crear_proceso(char *archivo, int tamanio, int prioridad);
void finalizar_proceso(int pid);
bool es_pcb_buscado(int pid_buscado, void *elemento);
t_tcb *crear_hilo(int prioridad, int ppid, int tid);
void planificador_largo_plazo();
bool finalizar_hilo(int pid, int tid, t_list *cola);
bool es_tcb_buscado(int pid_buscado, int tid_buscado, void *elemento);
void planificador_corto_plazo();
void ejecutar_fifo();
void ejecutar_prioridades();
void ejecutar_cmn();
void dispatcher(int tid, int pid);
void aviso_quantum(char *mensaje);
int get_index(int prioridad);
char *recibir_desde_memoria(int socket_cliente);
void aviso_quantum(char *mensaje);
char *recibir_desde_cpu(int socket_cliente);
void replanificar_hilo(int pid, int tid);
void desbloquear_hilos_join(int tid_join, int ppid);
void esperar_respuesta_dump_memory();

#endif