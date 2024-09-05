#include <../include/main_kernel.h>

t_log* logger;
t_config* config;
int socket_cpu_dispatch;
int socket_cpu_interrupt;
int socket_memoria;

int main(int argc, char* argv[]) {
    
    logger = iniciar_logger("./kernel.log", "kernel");
    config = iniciar_config(logger, "./kernel.config");

    //Inicia conexion con cpu dispatch
    char* ip_cpu = config_get_string_value(config, "IP_CPU");
    char* puerto_cpu_dispatch = config_get_string_value(config, "PUERTO_CPU_DISPATCH");
    socket_cpu_dispatch = crear_conexion(ip_cpu,puerto_cpu_dispatch);
    enviar_mensaje("Me conecto desde kernel (dispatch)!",socket_cpu_dispatch);
    

    //Inicia conexion con cpu interrupt
    char* puerto_cpu_interrupt = config_get_string_value(config, "PUERTO_CPU_INTERRUPT");
    socket_cpu_interrupt = crear_conexion(ip_cpu,puerto_cpu_interrupt);
    enviar_mensaje("Me conecto desde kernel (interrupt)!",socket_cpu_interrupt);

    //Inicia conexion con memoria
    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    socket_memoria = crear_conexion(ip_memoria,puerto_memoria);
    enviar_mensaje("Me conecto desde kernel!",socket_memoria);

    return 0;
}
