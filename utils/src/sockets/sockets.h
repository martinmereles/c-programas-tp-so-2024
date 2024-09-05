#ifndef SOCKETS_H_
#define SOCKETS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <errno.h>
#include <commons/error.h>
#include <commons/log.h>

// ---------------------------------------------------------------------------------------

// Obtener informacion de la red dado la IP y el PUERTO.
void obtener_info_red(char* modulo, char* IP, char* PUERTO, struct addrinfo *hints, struct addrinfo **server_info);
// Verificar si hubo error al obtener informacion de red.
void verificar_info_red(int err, char* modulo);
// Crear el socket del modulo.
int crear_socket(char* modulo, struct addrinfo *server_info);
// Verificar si hubo error al crear el socket.
void verificar_socket(int err, int *fd, char* modulo);

#endif