#include <../include/auxiliares_cpu.h>

t_paquete* crear_paquete_contexto(){

    //Crear paquete
    t_paquete* new_paquete = crear_paquete();

    //Agregar a paquete todos los registros
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
    
    //Enviar paquete a memoria
    enviar_paquete(new_paquete, socket_memoria);
}

char* recibir_desde_memoria(int socket_cliente){

	t_list* lista;
    int cod_op = recibir_operacion(socket_cliente);
    switch (cod_op) {
    case MENSAJE:
        int size;
        char* buffer = recibir_buffer(&size, socket_cliente);
        log_info(logger, "Me llego el mensaje %s", buffer);
        //void * mensaje;
        char* mensaje;
        if(string_starts_with(buffer, "CONTEXTO_GUARDADO")){
            mensaje = buffer;
        }
        free(buffer);
        return mensaje;
        break;
    case PAQUETE:
        lista = recibir_paquete(socket_cliente );
        log_info(logger, "Me llegaron los siguientes valores:\n");
        list_iterate(lista, (void*) iterator);
        break;
    case -1:
        log_error(logger, "el cliente se desconecto.");
        return EXIT_FAILURE;
    default:
        log_warning(logger,"Operacion desconocida. No quieras meter la pata");
        break;
    }
}

pthread_t iniciar_hilo_server_cpu(char *puerto){

	int socket_servidor = iniciar_servidor(puerto);
	
    pthread_t hiloAtencion;
    pthread_create(&hiloAtencion,
                    NULL,
                    (void *)hilo_cliente_cpu,
                    socket_servidor);

	return hiloAtencion;
}

void hilo_cliente_cpu(int socket_servidor){

	while(1){
		int socket_cliente = esperar_cliente(socket_servidor);
		pthread_t hiloCliente;
		pthread_create(&hiloCliente,
					   NULL,
					   (void *)atender_cliente_cpu,
					   socket_cliente);
		pthread_detach(hiloCliente);
	}
}

void atender_cliente_cpu(int socket_cliente){	

	t_list *lista;
	while (1){	
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

void recibir_mensaje_cpu(int socket_cliente){
    
	int size;
	char *buffer = recibir_buffer(&size, socket_cliente);
    if(string_starts_with(buffer, "CONEXION_INICIAL_KERNEL_DISPATCH")){
        soccket_kernel_dispatch = socket_cliente;
    }
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}