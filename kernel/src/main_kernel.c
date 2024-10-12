#include <../include/main_kernel.h>

t_log* logger;
t_config* config;
int socket_cpu_dispatch;
int socket_cpu_interrupt;
int socket_memoria;
t_list* QUEUE_NEW;
t_list* QUEUE_READY;
t_list* QUEUE_EXEC;
t_list* QUEUE_BLOCKED;
t_list* QUEUE_EXIT;
int contador_pid;
sem_t sem_largo_plazo;


int main(int argc, char** argv) {
    
    logger = iniciar_logger("./kernel.log", "kernel");
    config = iniciar_config(logger, "./kernel.config");
    QUEUE_NEW = list_create();
    QUEUE_READY = list_create();
    QUEUE_EXEC = list_create();
    QUEUE_BLOCKED = list_create();
    QUEUE_EXIT = list_create();
    contador_pid = 0;
    sem_init(&sem_largo_plazo,0,0);
    
    char* archivo = argv [1];
    int tamanio_proceso = atoi(argv[2]);


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

    // se inicia hilo planificador de largo plazo
    pthread_t hilo_planificador_largo;
    pthread_create(&hilo_planificador_largo,
                           NULL,
                           (void *)planificador_largo_plazo,
                           (void *)arg);
    pthread_join(hilo_planificador_largo, NULL);

    return 0;
    
}
