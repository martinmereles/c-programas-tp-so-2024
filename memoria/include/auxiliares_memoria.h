#ifndef _AUXILIARES_MEMORIA_H_
#define _AUXILIARES_MEMORIA_H_

#include <utils/estructuras.h>
#include <commons/string.h>
#include <utils/client-server.h>

//variables globales
extern t_log* logger;
extern t_config* config;
extern int socket_filesystem;
extern char* esquema;
extern t_list* procesos;
extern t_list* hilos;
extern int retardo_respuesta_cpu;
extern t_list *lista_particiones;
extern int tamanio_memoria;
extern char *algoritmo;

void crear_proceso(char *archivo_instrucciones, int tamanio, int prioridad, int pid, int socket_cliente);
void crear_hilo(char* archivo_instrucciones, int prioridad, int pid, int tid, int socket_cliente);
void leer_instrucciones (char* path, t_list* lista_instrucciones);
void atender_cliente_memoria(int socket_cliente);
void hilo_cliente_memoria(int socket_servidor);
pthread_t iniciar_hilo_server_memoria(char *puerto);
void entender_mensaje_memoria(t_atencion_mensaje* param_atencion);
void proxima_instruccion(int pid, int tid, int pc, int socket_cliente);
void obtener_contexto(int pid, int tid, int socket_cliente);
t_contexto_hilo *find_by_pid_tid(t_list *hilos, int pid, int tid);
void entender_paquete_memoria(t_atencion_paquete* param_atencion);
t_contexto_hilo *find_by_pid(t_list *procesos, int pid);
void iniciar_memoria_fija(char** particiones_array);
void iniciar_memoria_dinamica();
bool hay_espacio(int tamanio_necesario);
t_particion* asignar_particion(int tamanio, int pid);
t_particion *first_fit(int tamanio_necesario, int pid);
t_particion *best_fit(int tamanio_necesario, int pid);
t_particion *worst_fit(int tamanio_necesario, int pid);

#endif