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
    
    //Recibir respuesta de memoria PROXIMA_INSTRUCCION "INSTRUCCION"
    char* respuesta_memoria = recibir_desde_memoria(socket_memoria);
    instruccion_exec = string_substring_from(respuesta_memoria, 19);

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
}

void check_interrupt(){ // desde kernel se entienden los mensajes: "HILO PID TID INTERRUPCION_FIN_QUATUM",  "HILO PID TID INTERRUPCION_FIN_HILO", "HILO PID TID INTERRUPCION_I_O"
    
    //TO DO
}