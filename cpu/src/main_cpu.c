#include <../include/main_cpu.h>

t_log* logger;
t_config* config;
int socket_memoria;

int main(int argc, char* argv[]) {
    
    logger = iniciar_logger("./cpu.log", "cpu");
    config = iniciar_config(logger, "./cpu.config");

    //Inicia conexion con memoria
    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    socket_memoria = crear_conexion(ip_memoria,puerto_memoria);
    enviar_mensaje("Me conecto desde cpu!",socket_memoria);

    //Iniciar hilo servidor dispatch
    char* puerto_dispatch = config_get_string_value(config, "PUERTO_ESCUCHA_DISPATCH");
	pthread_t hilo_servidor_dispatch = iniciar_hilo_server(puerto_dispatch);
    pthread_detach(hilo_servidor_dispatch);
    
    //Iniciar hilo servidor interrupt
    char* puerto_interrupt = config_get_string_value(config, "PUERTO_ESCUCHA_INTERRUPT");
	pthread_t hilo_servidor_interrupt = iniciar_hilo_server(puerto_interrupt);

    //Inicio de ciclo de instruccion
    while(1){
		fetch();
		decode();
		execute();
		check_interrupt();
	}
    
    pthread_join(hilo_servidor_interrupt, NULL);

    return 0;
}
