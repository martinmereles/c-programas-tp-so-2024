#include <sockets/servidor/servidor.h>

int iniciar_conexion(char* modulo, char* cliente, char* PUERTO, t_log** logger) {
    // Loggear el estado iniciando socket de escucha.
    log_info(*logger, "Iniciando socket de escucha del modulo %s...", modulo);

    // Iniciar el servidor del modulo.
    int fd_escucha = iniciar_servidor(modulo, PUERTO);

    // Loggear el estado iniciado socket de escucha.
    log_info(*logger, "Se ha iniciado el socket de escucha del modulo %s correctamente", modulo);
    // Loggear el estado esperando cliente.
    log_info(*logger, "Esperando conexion con cliente...");

    // Aceptar a un nuevo cliente.
    int fd_conexion = accept(fd_escucha, NULL, NULL);

    // Loggear ek estado en conexion.
    log_info(*logger, "Se ha establecido conexion con el modulo %s", cliente);

    // Cerrar el socket de escucha del servidor.
    close(fd_escucha);

    // Retornar el socket de conexion.
    return fd_conexion;
}

int iniciar_servidor(char* modulo, char* PUERTO) {
    // Datos para la creacion del socket de escucha.
    struct addrinfo hints, *server_info;

    // Establecer hints.
    memset(&hints, 0, sizeof(hints));
    // Usar cualquier familia de direcciones (IPv4 o IPv6)
    hints.ai_family = AF_UNSPEC;
    // Usar tipo de socket TCP.
    hints.ai_socktype = SOCK_STREAM;
    // Especifica opciones adicionales (Al usar AI_PASSIVE se establece un socket escucha)
    hints.ai_flags = AI_PASSIVE;

    // Obtener informacion de la red dado el PUERTO de escucha.
    obtener_info_red(modulo, NULL, PUERTO, &hints, &server_info);
    // Crear el socket de escucha.
    int fd_escucha = crear_socket(modulo, server_info);
    // Asociar el socket a un puerto.
    asociar_puerto(modulo, &fd_escucha, server_info);
    // Referenciar al socket que se utilizará para aceptar solicitudes de conexión entrantes.
    escuchar_socket(modulo, &fd_escucha);

    // Liberar la memoria del server_info.
    freeaddrinfo(server_info);

    // Retornar el socket de escucha.
    return fd_escucha;
}

void asociar_puerto(char* modulo, int *fd_escucha, struct addrinfo *server_info) {
    // Asociar el socket a un puerto.
    int err = bind(*fd_escucha, server_info->ai_addr, server_info->ai_addrlen);
    // Verificar si hubo error al asociar el socket a un puerto.
    verificar_socket(err, fd_escucha, modulo);
}

void escuchar_socket(char* modulo, int *fd_escucha) {
    // Escuchar el socket.
    int err = listen(*fd_escucha, SOMAXCONN);
    // Verificar si hubo error al escuchar el socket.
    verificar_socket(err, fd_escucha, modulo);
}