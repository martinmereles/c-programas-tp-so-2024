#include <../include/auxiliares_cpu.h>

void *crear_paquete_contexto()
{

    // Crear paquete
    t_paquete *new_paquete = crear_paquete();

    char *mensaje = string_new();
    string_append(&mensaje, "ACTUALIZAR_CONTEXTO");

    // Agregar a paquete todos los registros
    agregar_a_paquete(new_paquete, mensaje, string_length(mensaje) + 1);
    agregar_a_paquete(new_paquete, string_itoa(pid), string_length(string_itoa(pid))+1);
    agregar_a_paquete(new_paquete, string_itoa(tid), string_length(string_itoa(tid))+1);
    agregar_a_paquete(new_paquete, string_itoa(PC), string_length(string_itoa(PC)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(AX), string_length(string_itoa(AX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(BX), string_length(string_itoa(BX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(CX), string_length(string_itoa(CX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(DX), string_length(string_itoa(DX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(EX), string_length(string_itoa(EX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(FX), string_length(string_itoa(FX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(GX), string_length(string_itoa(GX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(HX), string_length(string_itoa(HX)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(BASE), string_length(string_itoa(BASE)) + 1);
    agregar_a_paquete(new_paquete, string_itoa(LIMITE), string_length(string_itoa(LIMITE)) + 1);

    // Enviar paquete a memoria
    enviar_paquete(new_paquete, socket_memoria);
    log_info(logger, "##TID: %d - Actualizo Contexto Ejecución", tid);
    //Esperar mensaje resultado CONTEXTO_GUARDADO
    char* respuesta_memoria = recibir_desde_memoria(socket_memoria);
}

char *recibir_desde_memoria(int socket_cliente)
{

    t_list *lista;
    char* mensaje;
    int cod_op = recibir_operacion(socket_cliente);
    switch (cod_op)
    {
    case MENSAJE:
        int size;
        char *buffer = recibir_buffer(&size, socket_cliente);
        if (string_starts_with(buffer, "CONTEXTO_GUARDADO") || string_starts_with(buffer, "WRITE_MEM") 
            || string_starts_with(buffer, "PROXIMA_INSTRUCCION") || string_starts_with(buffer, "ACTUALIZAR_CONTEXTO"))
        {
            mensaje = string_duplicate(buffer);
        }
        free(buffer);
        return mensaje;
        break;
    case PAQUETE:
        lista = recibir_paquete(socket_cliente);
        entender_paquete_memoria(lista);
        mensaje = list_get(lista, 0);
        log_info(logger, "Me llegaron los siguientes valores:\n");
        list_iterate(lista, (void *)iterator);
        return mensaje;
        break;
    case -1:
        log_error(logger, "el cliente se desconecto.");
        return EXIT_FAILURE;
    default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata");
        break;
    }
}

// Funciones hilo dispatch
pthread_t iniciar_hilo_server_dispatch(char *puerto)
{

    int socket_servidor = iniciar_servidor(puerto);

    pthread_t hiloAtencion;
    pthread_create(&hiloAtencion,
                   NULL,
                   (void *)hilo_cliente_dispatch,
                   socket_servidor);

    return hiloAtencion;
}

void hilo_cliente_dispatch(int socket_servidor)
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

void atender_cliente_dispatch(int socket_cliente_dispatch)
{

    t_list *lista;
    log_info(logger, "El socket_servidor_dispatch es : %d", socket_cliente_dispatch);
    while (1)
    {
        int cod_op = recibir_operacion(socket_cliente_dispatch);

        switch (cod_op)
        {
        case MENSAJE:
            int size;
            char *buffer = recibir_buffer(&size, socket_cliente_dispatch);
            log_info(logger, "Me llego el mensaje %s", buffer);
            char **mensaje_split = string_split(buffer, " ");
            if (strcmp(buffer, "CONEXION_INICIAL_KERNEL_DISPATCH") == 0)
            {
                socket_kernel_dispatch = socket_cliente_dispatch;
            }
            else if (strcmp(mensaje_split[0], "PROXIMO_PROCESO") == 0)
            {
                proximo_proceso(mensaje_split[1], mensaje_split[2]);
            }
            free(buffer);
            break;
        case PAQUETE:
            lista = recibir_paquete(socket_cliente_dispatch);
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
// Fin funciones dispatch

// Inicio funciones interrupt
pthread_t iniciar_hilo_server_interrupt(char *puerto)
{

    int socket_servidor = iniciar_servidor(puerto);

    pthread_t hiloAtencion;
    pthread_create(&hiloAtencion,
                   NULL,
                   (void *)hilo_cliente_interrupt,
                   socket_servidor);

    return hiloAtencion;
}

void hilo_cliente_interrupt(int socket_servidor)
{

    while (1)
    {
        int socket_cliente = esperar_cliente(socket_servidor);
        pthread_t hiloCliente;
        pthread_create(&hiloCliente,
                       NULL,
                       (void *)atender_cliente_interrupt,
                       socket_cliente);
        pthread_detach(hiloCliente);
    }
}

void atender_cliente_interrupt(int socket_cliente_interrupt)
{

    t_list *lista;
    int size;
    while (1)
    {
        int cod_op = recibir_operacion(socket_cliente_interrupt);

        switch (cod_op)
        {
        case MENSAJE:
            char *buffer = recibir_buffer(&size, socket_cliente_interrupt);
            char **mensaje_split = string_split(buffer, " ");
            if (strcmp(mensaje_split[0], "FIN_QUANTUM") == 0){
                char* nueva_interrupcion = string_new();
                nueva_interrupcion = string_duplicate(buffer);
                list_add(interrupciones, nueva_interrupcion);
                log_info(logger, "## Llega interrupción al puerto Interrupt");
            }
            free(buffer);
            break;
        case PAQUETE:
            lista = recibir_paquete(socket_cliente_interrupt);
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
// Fin funciones interrupt

void proximo_proceso(char *pid_nuevo, char *tid_nuevo)
{

    // Actualizamos con nuevo pid y tid global
    pid = atoi(pid_nuevo);
    tid = atoi(tid_nuevo);

    // Mensaje a memoria para recibir contexto
    char *mensaje = string_new();
    string_append(&mensaje, "OBTENER_CONTEXTO ");
    string_append(&mensaje, pid_nuevo);
    string_append(&mensaje, " ");
    string_append(&mensaje, tid_nuevo);
    enviar_mensaje(mensaje, socket_memoria);
    log_info(logger, "##TID: %d - Solicito Contexto Ejecución", tid);

    // Esperar respuesta memoria
    t_list *lista;

    int cod_op = recibir_operacion(socket_memoria);

    switch (cod_op)
    {
    case MENSAJE:
        recibir_mensaje(socket_memoria);
        break;
    case PAQUETE:
        lista = recibir_paquete(socket_memoria);
        entender_paquete_memoria(lista);
        break;
    case -1:
        log_error(logger, "El cliente se desconecto.");
        return EXIT_FAILURE;
    default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata.");
        break;
    }
}

void entender_paquete_memoria(t_list *lista)
{
    if (string_starts_with(list_get(lista, 0), "OBTENER_CONTEXTO"))
    {
        actualizar_contexto_cpu(lista);
    }else if(string_starts_with(list_get(lista, 0), "READ_MEM")){
        actualizar_registro(list_get(lista, 1));
    }
}

void actualizar_contexto_cpu(t_list *lista)
{

    PC = atoi(list_get(lista, 3));
    AX = atoi(list_get(lista, 4));
    BX = atoi(list_get(lista, 5));
    CX = atoi(list_get(lista, 6));
    DX = atoi(list_get(lista, 7));
    EX = atoi(list_get(lista, 8));
    FX = atoi(list_get(lista, 9));
    GX = atoi(list_get(lista, 10));
    HX = atoi(list_get(lista, 11));
    BASE = atoi(list_get(lista, 12));
    LIMITE = atoi(list_get(lista, 13));

    //Iniciar ciclo_instruccion
    sem_post(&sem_execute);
}

void actualizar_registro(char* dato){
    char ** instruccion_exec_split = string_split(instruccion_exec, " ");
    char *registro_datos = instruccion_exec_split[1];
    set(registro_datos, dato);
}

void validar_interrupcion(char* pid, char* tid){

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