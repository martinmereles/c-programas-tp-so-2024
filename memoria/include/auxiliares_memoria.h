#ifndef _AUXILIARES_MEMORIA_H_
#define _AUXILIARES_MEMORIA_H_

#include <utils/estructuras.h>

//variables globales
extern t_log* logger;
extern t_config* config;
extern int socket_filesystem;
extern char* esquema;
extern t_list* procesos;
extern t_list* hilos;

void crear_proceso (int pid, int tid,  char* archivo_instrucciones);
crear_hilo(char* archivo_instrucciones, int prioridad, int pid, int tid);
void leer_intrucciones (char* path, t_list* lista_instrucciones);
#endif