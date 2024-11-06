#include <../include/ciclo_instruccion.h>

void fetch(){

    log_info(logger, "## TID: %d - FETCH - Program Counter: %d", tid, PC);
    char* mensaje = string_new();
    string_append(&mensaje,"PROXIMA_INSTRUCCION ");
    string_append(&mensaje, pid);
    string_append(&mensaje, " ");
    string_append(&mensaje, tid);
    string_append(&mensaje, " ");
    string_append(&mensaje, PC);
    enviar_mensaje(mensaje ,socket_memoria);
    
    //Recibir respuesta de memoria
    char* respuesta_memoria = recibir_desde_memoria(socket_memoria);

}

void decode(){

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

void execute(){

    ejecutarSentencia(socket_memoria);
    //TO DO
}

void check_interrupt(){
    
    //TO DO
}