#include <sockets/sockets.h>

// ---------------------------------------------------------------------------------------

void obtener_info_red(char* modulo, char* IP, char* PUERTO, struct addrinfo *hints, struct addrinfo **server_info) {
    // Obtener informacion de la red dado la IP y el PUERTO.
    int err = getaddrinfo(IP, PUERTO, hints, server_info);
    // Verificar si hubo error al obtener informacion de red (Si lo hubo, err sera distinto a 0)
    verificar_info_red(err, modulo);
}

void verificar_info_red(int err, char* modulo) {
    // Verificar si ocurrio un error al obtener informacion de la red.
    if(err != 0) {
        // Imprimir por pantalla el mensaje de error.
        error_show("Error al obtener informacion de red en modulo %s", modulo);
        // Abortar programa.
        abort();
    }
}

int crear_socket(char* modulo, struct addrinfo *server_info) {
    // Crear el socket del modulo.
    int fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    // Verificar si hubo error al crear socket.
    verificar_socket(fd, &fd, modulo);

    // Retornar el socket.
    return fd;
}

void verificar_socket(int err, int *fd, char* modulo) {
    // Verificar si ocurrio un error en el socket.
    if(err == -1) {
        // Imprimir por pantalla el mensaje de error.
        error_show("Error en el socket del modulo %s", modulo);
        // Cerrar socket.
        if (fd != NULL) close(*fd);
        // Abortar programa.
        abort();
    }
}