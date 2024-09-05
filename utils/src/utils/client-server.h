#ifndef UTILS_CLIENT_SERVER_H_
#define UTILS_CLIENT_SERVER_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <readline/readline.h>

typedef enum
{
	MENSAJE,
	PAQUETE

}op_code;

typedef struct
{
	int size;
	void* stream;

} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;

} t_paquete;

extern t_log* logger;

void atender_cliente(int socket_cliente);

pthread_t iniciar_hilo_server(char *puerto);

void iterator(char *value);

void liberar_conexion(int socket_cliente);

void eliminar_paquete(t_paquete *paquete);

void enviar_paquete(t_paquete *paquete, int socket_cliente);

void agregar_a_paquete(t_paquete *paquete, void *valor, int tamanio);

t_paquete *crear_paquete(void);

void crear_buffer(t_paquete *paquete);

void enviar_mensaje(char *mensaje, int socket_cliente);

int crear_conexion(char *ip, char *puerto);

void *serializar_paquete(t_paquete *paquete, int bytes);

t_list *recibir_paquete(int socket_cliente);

void recibir_mensaje(int socket_cliente);

void *recibir_buffer(int *size, int socket_cliente);

int recibir_operacion(int socket_cliente);

int esperar_cliente(int socket_servidor);

int iniciar_servidor(char *puerto);

#endif