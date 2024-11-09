#ifndef AUXILIARES_CPU_H
#define AUXILIARES_CPU_H

/*------------------------LIBRERIAS------------------------*/
#include <utils/estructuras.h>
#include <utils/client-server.h>
#include <commons/string.h>

/*------------------------VARIABLES------------------------*/
extern int socket_kernel_dispatch;
extern int socket_memoria;
extern int pid;
extern int tid;
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
extern sem_t sem_execute;
/*------------------------DECLARACIONES------------------------*/
t_paquete* crear_paquete_contexto();
char* recibir_desde_memoria(int socket_cliente);
pthread_t iniciar_hilo_server_dispatch(char *puerto);
pthread_t iniciar_hilo_server_interrupt(char *puerto);
void hilo_cliente_dispatch(int socket_servidor);
void hilo_cliente_interrupt(int socket_servidor);
void atender_cliente_dispatch(int socket_servidor_dispatch);
void atender_cliente_interrupt(int socket_cliente);
void proximo_proceso(char* pid_nuevo, char* tid_nuevo);
void entender_paquete_memoria(t_list*  lista);
void actualizar_contexto_cpu(t_list* lista);
uint32_t get_valor_registro(char * registro);

#endif