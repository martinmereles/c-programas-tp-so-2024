#include <../include/main_memoria.h>

t_log* logger;
t_config* config;
int socket_filesystem;
char* esquema;
t_list* procesos;
t_list* hilos;
int retardo_respuesta_cpu;


int main(int argc, char* argv[]) {

    //Inicializacion de variables
    logger = iniciar_logger("./memoria.log", "memoria");
    config = iniciar_config(logger, "./memoria.config");
    esquema = config_get_string_value(config, "ESQUEMA");
    retardo_respuesta_cpu = config_get_int_value(config, "RETARDO_RESPUESTA");
    procesos = list_create();
    hilos = list_create();

    //Inicia conexion con filesystem
    char* ip_filesystem = config_get_string_value(config, "IP_FILESYSTEM");
    char* puerto_filesystem = config_get_string_value(config, "PUERTO_FILESYSTEM");
    socket_filesystem = crear_conexion(ip_filesystem,puerto_filesystem);
    enviar_mensaje("Me conecto desde memoria!",socket_filesystem);

    //Iniciar hilo servidor
    char* puerto = config_get_string_value(config, "PUERTO_ESCUCHA");
	pthread_t hilo_servidor = iniciar_hilo_server_memoria(puerto);

    pthread_join(hilo_servidor, NULL);
    
    return 0;
}
