#include <../include/ciclo_instruccion.h>

void fetch(int socket_cliente_memoria){

    //log_info(logger, "## TID: %s - FETCH - Program Counter: %s", tid, program_counter);
    char* mensaje = string_new();
    string_append(&mensaje,"PROXIMA_INSTRUCCION ");
    string_append(&mensaje, pid);
    string_append(&mensaje, " ");
    string_append(&mensaje, tid);
    string_append(&mensaje, " ");
    string_append(&mensaje, PC);
    enviar_mensaje(mensaje ,socket_cliente_memoria);
    //Recibir respuesta de memoria
}

void decode(int socket_cliente_memoria){
    char* instruccion_exec;
    char ** instruccion_exec_split = string_split(instruccion_exec, " ");
    if(strcmp(instruccion_exec_split[0],"READ_MEM") == 0){
        //
    }
    if(strcmp(instruccion_exec_split[0],"WRITE_MEM") == 0){
        //
    }
    //TO DO
}

void execute(int socket_cliente_memoria){
    ejecutarSentencia(socket_cliente_memoria);
    //TO DO
}

void check_interrupt(int socket_cliente_memoria){
    //TO DO
}