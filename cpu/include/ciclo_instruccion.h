#ifndef CICLO_INSTRUCCION_H_
#define CICLO_INSTRUCCION_H_

/*------------------------LIBRERIAS------------------------*/
#include <commons/string.h>

/*------------------------DECLARACIONES------------------------*/
void fetch(int socket_cliente_memoria);
void decode(int socket_cliente_memoria);
void execute(int socket_cliente_memoria);
void check_interrupt(int socket_cliente_memoria);

#endif