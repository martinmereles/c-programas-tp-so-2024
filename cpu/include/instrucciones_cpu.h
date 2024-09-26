#ifndef INSTRUCCIONES_CPU_H
#define INSTRUCCIONES_CPU_H

/*------------------------LIBRERIAS------------------------*/
#include <../include/auxiliares.h>

/*------------------------DECLARACIONES------------------------*/
void set(char *registro, char *valor);
void read_mem();
void write_mem();
void sum(char *registro_destino, char *registro_origen);
void sub(char *registro_destino, char *registro_origen);
void jnz(char *registro, char *instruccion);
void log();

#endif