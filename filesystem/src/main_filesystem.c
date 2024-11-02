#include <../include/main_filesystem.h>

t_log* logger;
t_config* config;
char* mount_dir;
int block_size;
int block_count;
int retardo;
t_log_level log_level;
sem_t fs_en_uso;
t_bitarray* bitmap_bloques_libres;

int main(int argc, char* argv[]) {

    //Iniciar variables
    logger = iniciar_logger("./filesystem.log", "filesystem");
    config = iniciar_config(logger, "./filesystem.config");
    mount_dir = config_get_string_value(config, "MOUNT_DIR");
    block_size = config_get_int_value(config, "BLOCK_SIZE");
    block_count = config_get_int_value(config, "BLOCK_COUNT");
    retardo = config_get_int_value(config, "RETARDO_ACCESO_BLOQUE");
    char* log_level_string = config_get_string_value(config, "LOG_LEVEL");
    log_level = log_level_from_string(log_level_string);
    sem_init(&fs_en_uso, 0, 1);

    //Iniciar FS
    iniciar_fs();

    //Iniciar hilo servidor
    char* puerto = config_get_string_value(config, "PUERTO_ESCUCHA");
	pthread_t hilo_servidor = iniciar_hilo_server(puerto);




    pthread_join(hilo_servidor, NULL);

    return 0;
}
