#include <../include/main_filesystem.h>

t_log* logger;
t_config* config;

int main(int argc, char* argv[]) {

    logger = iniciar_logger("./filesystem.log", "filesystem");
    config = iniciar_config(logger, "./filesystem.config");


    //Iniciar hilo servidor
    char* puerto = config_get_string_value(config, "PUERTO_ESCUCHA");
	pthread_t hilo_servidor = iniciar_hilo_server(puerto);

    pthread_join(hilo_servidor, NULL);

    return 0;
}
