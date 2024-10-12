#ifndef AUXILIARES_CPU_H
#define AUXILIARES_CPU_H

/*------------------------LIBRERIAS------------------------*/
#include <utils/estructuras.h>
#include <utils/client-server.h>

/*------------------------VARIABLES------------------------*/
extern int socket_kernel_dispatch;
extern int socket_memoria;
extern uint32_t PC;
extern uint32_t AX;
extern uint32_t BX;
extern uint32_t CX;
extern uint32_t DX;
extern uint32_t EX;
extern uint32_t FX;
extern uint32_t GX;
extern uint32_t HX;
extern uint32_t BASE;
extern uint32_t LIMITE;
/*------------------------DECLARACIONES------------------------*/
t_paquete* crear_paquete_contexto();
char* recibir_desde_memoria(int socket_cliente);
pthread_t iniciar_hilo_server_cpu(char *puerto);
void hilo_cliente_cpu(int socket_servidor);
void atender_cliente_cpu(int socket_cliente);
void recibir_mensaje_cpu(int socket_cliente);

#endif