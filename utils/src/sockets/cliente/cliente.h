#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <sockets/sockets.h>

// ---------------------------------------------------------------------------------------

// Iniciar cliente del modulo.
int iniciar_cliente(char* modulo, char* servidor, char* IP, char* PUERTO, t_log** logger);
// Conectar con el socket del servidor.
void conectar_socket(char* modulo, struct addrinfo *server_info, int *fd_conexion);

#endif