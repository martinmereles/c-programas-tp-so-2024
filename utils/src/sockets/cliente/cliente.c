#include <sockets/cliente/cliente.h>

int iniciar_cliente(char* modulo, char* servidor, char* IP, char* PUERTO, t_log** logger) {
    // Loggear el estado iniciando socket de escucha.
    log_info(*logger, "Iniciando socket de conexion con modulo %s...", servidor);

    // Datos para la creacion del socket de escucha.
    struct addrinfo hints, *server_info;

    // Establecer hints.
    memset(&hints, 0, sizeof(hints));
    // Usar cualquier familia de direcciones (IPv4 o IPv6)
    hints.ai_family = AF_UNSPEC;
    // Usar tipo de socket TCP.
    hints.ai_socktype = SOCK_STREAM;
    
    // Obtener informacion de la red.
    obtener_info_red(modulo, IP, PUERTO, &hints, &server_info);
    // Crear el socket del cliente.
    int fd_conexion = crear_socket(modulo, server_info);

    // Loggear el estado iniciado socket de conexion.
    log_info(*logger, "Se ha iniciado el socket de conexion del modulo %s correctamente", modulo);
    // Loggear el estado conectando cliente.
    log_info(*logger, "Conectando con el modulo %s...", servidor);

    // Conectar el cliente con el socket servidor.
    conectar_socket(modulo, server_info, &fd_conexion);

    // Loggear el estado en conexion.
    log_info(*logger, "Se ha establecido conexion con el modulo %s", servidor);

    // Liberar la memoria del server_info.
    freeaddrinfo(server_info);

    // Retornar el socket de conexion.
    return fd_conexion;
}

void conectar_socket(char* modulo, struct addrinfo *server_info, int *fd_conexion) {
    // Conectar el cliente con el socket servidor.
    int err = connect(*fd_conexion, server_info->ai_addr, server_info->ai_addrlen);
    // Verificar si hubo error al conectar el cliente con el socket servidor.
    verificar_socket(err, fd_conexion, modulo);
}