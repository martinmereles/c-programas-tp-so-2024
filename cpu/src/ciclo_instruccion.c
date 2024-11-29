#include <../include/ciclo_instruccion.h>

void fetch(){

    char* mensaje = string_new();
    string_append(&mensaje,"PROXIMA_INSTRUCCION ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(PC));
    enviar_mensaje(mensaje ,socket_memoria);
    
    //Recibir respuesta de memoria PROXIMA_INSTRUCCION "INSTRUCCION"
    char* respuesta_memoria = recibir_desde_memoria(socket_memoria);
    instruccion_exec = string_substring_from(respuesta_memoria, 20);
    log_info(logger, "## TID: %d - FETCH - Program Counter: %d", tid, PC);
}

void decode(){

    char ** instruccion_exec_split = string_split(instruccion_exec, " ");
    if(strcmp(instruccion_exec_split[0],"READ_MEM") == 0){
        char *registro_direccion = instruccion_exec_split[2];
        int valor_registro_direccion = get_valor_registro(registro_direccion);
        validar_direccion(valor_registro_direccion);
    }
    if(strcmp(instruccion_exec_split[0],"WRITE_MEM") == 0){
        char *registro_direccion = instruccion_exec_split[1];
        int valor_registro_direccion = get_valor_registro(registro_direccion);
        validar_direccion(valor_registro_direccion);   
    }
}

void execute(){

    ejecutarSentencia();
    PC++;
}

void check_interrupt(){ // desde kernel se entienden los mensajes: "HILO PID TID INTERRUPCION_FIN_QUANTUM",  "HILO PID TID INTERRUPCION_FIN_HILO", "HILO PID TID INTERRUPCION_I_O"
    
    for(int i = 0; i < list_size(interrupciones); i++){

        char ** interrupcion_split = string_split(list_get(interrupciones, i), " ");

        if(strcmp(interrupcion_split[1], string_itoa(pid)) == 0 && strcmp(interrupcion_split[2], string_itoa(tid)) == 0){
            if(strcmp(interrupcion_split[0],"FIN_QUANTUM") == 0){
                //Envio mensaje a memoria junto al contexto para actualizar
                crear_paquete_contexto();
                //Envio mensaje a Kernel con Motivo, pid y tid
                char* mensaje = string_new();
                string_append(&mensaje, pid);
                string_append(&mensaje, " ");
                string_append(&mensaje, tid);
                string_append(&mensaje, " ");
                string_append(&mensaje,"INTERRUPCION_FIN_QUANTUM");
                enviar_mensaje(mensaje ,socket_kernel_dispatch);
                //Espero al proximo proceso
                sem_wait(&sem_execute);
            }
            list_clean(interrupciones);
        }
    }
}