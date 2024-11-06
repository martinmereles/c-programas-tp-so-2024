#include <../include/auxiliares_cpu.h>

t_paquete *crear_paquete_contexto()
{

    // Crear paquete
    t_paquete *new_paquete = crear_paquete();

    char *mensaje = string_new();
    string_append(&mensaje, "ACTUALIZAR_CONTEXTO");

    // Agregar a paquete todos los registros
    agregar_a_paquete(new_paquete, mensaje, sizeof(mensaje));
    agregar_a_paquete(new_paquete, pid, sizeof(int));
    agregar_a_paquete(new_paquete, tid, sizeof(int));
    agregar_a_paquete(new_paquete, PC, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, AX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, BX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, CX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, DX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, EX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, FX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, GX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, HX, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, BASE, sizeof(u_int32_t));
    agregar_a_paquete(new_paquete, LIMITE, sizeof(u_int32_t));

    // Enviar paquete a memoria
    enviar_paquete(new_paquete, socket_memoria);
    log_info(logger, "##TID: %d - Actualizo Contexto Ejecución", tid);
}

char *recibir_desde_memoria(int socket_cliente)
{

    t_list *lista;
    int cod_op = recibir_operacion(socket_cliente);
    switch (cod_op)
    {
    case MENSAJE:
        int size;
        char *buffer = recibir_buffer(&size, socket_cliente);
        log_info(logger, "Me llego el mensaje %s", buffer);
        // void * mensaje;
        char *mensaje;
        if (string_starts_with(buffer, "CONTEXTO_GUARDADO"))
        {
            mensaje = buffer;
        }
        free(buffer);
        return mensaje;
        break;
    case PAQUETE:
        lista = recibir_paquete(socket_cliente);
        log_info(logger, "Me llegaron los siguientes valores:\n");
        list_iterate(lista, (void *)iterator);
        break;
    case -1:
        log_error(logger, "el cliente se desconecto.");
        return EXIT_FAILURE;
    default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata");
        break;
    }
}

pthread_t iniciar_hilo_server_dispatch(char *puerto)
{

    int socket_servidor = iniciar_servidor(puerto);

    pthread_t hiloAtencion;
    pthread_create(&hiloAtencion,
                   NULL,
                   (void *)hilo_cliente_cpu,
                   socket_servidor);

    return hiloAtencion;
}

void hilo_cliente_cpu(int socket_servidor)
{

    while (1)
    {
        int socket_cliente = esperar_cliente(socket_servidor);
        pthread_t hiloCliente;
        pthread_create(&hiloCliente,
                       NULL,
                       (void *)atender_cliente_dispatch,
                       socket_cliente);
        pthread_detach(hiloCliente);
    }
}

void atender_cliente_cpu(int socket_cliente)
{

    t_list *lista;
    while (1)
    {
        int cod_op = recibir_operacion(socket_cliente);

        switch (cod_op)
        {
        case MENSAJE:
            recibir_mensaje(socket_cliente);
            break;
        case PAQUETE:
            lista = recibir_paquete(socket_cliente);
            log_info(logger, "Me llegaron los siguientes valores:\n");
            list_iterate(lista, (void *)iterator);
            break;
        case -1:
            log_error(logger, "El cliente se desconecto.");
            return EXIT_FAILURE;
        default:
            log_warning(logger, "Operacion desconocida. No quieras meter la pata.");
            break;
        }
    }
}

void atender_cliente_dispatch(int socket_servidor_dispatch)
{

    t_list *lista;
    log_info(logger, "El socket_servidor_dispatch es : %d", socket_servidor_dispatch);
    while (1)
    {
        int cod_op = recibir_operacion(socket_servidor_dispatch);

        switch (cod_op)
        {
        case MENSAJE:
            int size;
            char *buffer = recibir_buffer(&size, socket_servidor_dispatch);
            log_info(logger, "Me llego el mensaje %s", buffer);
            char** mensaje_split = string_split(buffer, " ");
            if (strcmp(mensaje_split[0], "PROXIMO_PROCESO") == 0){
                proximo_proceso(mensaje_split[1], mensaje_split[2]);
            }
            free(buffer);
            break;
        case PAQUETE:
            lista = recibir_paquete(socket_servidor_dispatch);
            log_info(logger, "Me llegaron los siguientes valores:\n");
            list_iterate(lista, (void *)iterator);
            break;
        case -1:
            log_error(logger, "El cliente se desconecto.");
            return EXIT_FAILURE;
        default:
            log_warning(logger, "Operacion desconocida. No quieras meter la pata.");
            break;
        }
    }
}

void atender_cliente_interrupt(int socket_cliente)
{

    t_list *lista;
    while (1)
    {
        int cod_op = recibir_operacion(socket_cliente);

        switch (cod_op)
        {
        case MENSAJE:
            recibir_mensaje(socket_cliente);
            break;
        case PAQUETE:
            lista = recibir_paquete(socket_cliente);
            log_info(logger, "Me llegaron los siguientes valores:\n");
            list_iterate(lista, (void *)iterator);
            break;
        case -1:
            log_error(logger, "El cliente se desconecto.");
            return EXIT_FAILURE;
        default:
            log_warning(logger, "Operacion desconocida. No quieras meter la pata.");
            break;
        }
    }
}

void recibir_mensaje_cpu(int socket_cliente)
{

    int size;
    char *buffer = recibir_buffer(&size, socket_cliente);
    if (string_starts_with(buffer, "CONEXION_INICIAL_KERNEL_DISPATCH"))
    {
        socket_kernel_dispatch = socket_cliente;
    }
    log_info(logger, "Me llego el mensaje %s", buffer);
    free(buffer);
}

void proximo_proceso(char* pid_nuevo, char* tid_nuevo){

    //Actualizamos con nuevo pid y tid global
    pid = atoi(pid_nuevo);
    tid = atoi(tid_nuevo);

    //Mensaje a memoria para recibir contexto
    char* mensaje = string_new();
    string_append(&mensaje,"OBTENER_CONTEXTO ");
    string_append(&mensaje, pid_nuevo);
    string_append(&mensaje, " ");
    string_append(&mensaje, tid_nuevo);
    enviar_mensaje(mensaje, socket_memoria);
    log_info(logger, "##TID: %d - Solicito Contexto Ejecución", tid_nuevo);

    //Esperar respuesta memoria
    t_list* lista;
    lista = recibir_paquete(socket_memoria);
    //Actualizamos registros contexto cpu
    entender_paquete_memoria(lista);
}

void entender_paquete_memoria(t_list *lista)
{
  if (string_starts_with(list_get(lista, 0), "OBTENER_CONTEXTO"))
  {
    actualizar_contexto_cpu(lista);
  }
}

void actualizar_contexto_cpu(t_list* lista){

    PC = list_get(lista, 3);
    AX = list_get(lista, 4);
    BX = list_get(lista, 5);
    CX = list_get(lista, 6);
    DX = list_get(lista, 7);
    EX = list_get(lista, 8);
    FX = list_get(lista, 9);
    GX = list_get(lista, 10);
    HX = list_get(lista, 11);
    BASE = list_get(lista, 12);
    LIMITE = list_get(lista, 13);
}

uint32_t get_valor_registro(char * registro){
    if(strcmp(registro,"PC") == 0){return PC;}
    if(strcmp(registro,"AX") == 0){return AX;}
    if(strcmp(registro,"BX") == 0){return BX;}
    if(strcmp(registro,"CX") == 0){return CX;}
    if(strcmp(registro,"DX") == 0){return DX;}
    if(strcmp(registro,"EX") == 0){return EX;}
    if(strcmp(registro,"FX") == 0){return FX;}
    if(strcmp(registro,"GX") == 0){return GX;}
    if(strcmp(registro,"HX") == 0){return HX;}
    if(strcmp(registro,"BASE") == 0){return BASE;}
    if(strcmp(registro,"LIMITE") == 0){return LIMITE;}
}