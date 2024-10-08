#ifndef INSTRUCCIONES_CPU_H
#define INSTRUCCIONES_CPU_H

/*------------------------LIBRERIAS------------------------*/
#include <../include/auxiliares.h>

/*------------------------DECLARACIONES------------------------*/
void set(char *registro, char *valor);
void read_mem(char* registro_datos, char* registro_direccion);
void write_mem(char* registro_direccion, char* registro_datos);
void sum(char *registro_destino, char *registro_origen);
void sub(char *registro_destino, char *registro_origen);
void jnz(char *registro, char *instruccion);
void log(char* registro);
void ejecutarSentencia(int socket_cliente_memoria);

#endif