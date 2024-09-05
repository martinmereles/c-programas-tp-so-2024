#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <sockets/sockets.h>

// ---------------------------------------------------------------------------------------

// Iniciar socket de conexion de un modulo.
int iniciar_conexion(char* modulo, char* cliente, char* PUERTO, t_log** logger);
// Iniciar socket de escucha de un modulo.
int iniciar_servidor(char* modulo, char* PUERTO);
// Asociar el socket a un puerto.
void asociar_puerto(char* modulo, int *fd_escucha, struct addrinfo *server_info);
// Referenciar al socket que se utilizará para aceptar solicitudes de conexión entrantes.
void escuchar_socket(char* modulo, int *fd_escucha);

#endif