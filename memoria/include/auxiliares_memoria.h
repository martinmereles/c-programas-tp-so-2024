#ifndef _AUXILIARES_MEMORIA_H_
#define _AUXILIARES_MEMORIA_H_

#include <utils/estructuras.h>
#include <commons/string.h>

//variables globales
extern t_log* logger;
extern t_config* config;
extern int socket_filesystem;
extern char* esquema;
extern t_list* procesos;
extern t_list* hilos;

void crear_proceso(char *archivo_instrucciones, int tamanio, int prioridad, int pid);
void crear_hilo(char* archivo_instrucciones, int prioridad, int pid, int tid);
void leer_instrucciones (char* path, t_list* lista_instrucciones);
#endif