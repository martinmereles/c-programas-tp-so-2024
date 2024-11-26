#include <../include/main_filesystem.h>

t_log *logger;
t_config *config;
char *mount_dir;
int block_size;
int block_count;
int retardo;
sem_t fs_en_uso;
t_bitarray *bitmap_bloques_libres;

int main(int argc, char *argv[])
{

    // Iniciar variables

    config = iniciar_config("./filesystem.config");
    char *log_level_string = config_get_string_value(config, "LOG_LEVEL");
    logger = iniciar_logger("./filesystem.log", "filesystem", log_level_string);
    mount_dir = config_get_string_value(config, "MOUNT_DIR");
    block_size = config_get_int_value(config, "BLOCK_SIZE");
    block_count = config_get_int_value(config, "BLOCK_COUNT");
    retardo = config_get_int_value(config, "RETARDO_ACCESO_BLOQUE");

    sem_init(&fs_en_uso, 0, 1);

    // Iniciar FS
    iniciar_fs();

    // Iniciar hilo servidor
    char *puerto = config_get_string_value(config, "PUERTO_ESCUCHA");
    pthread_t hilo_servidor = iniciar_hilo_server_fs(puerto);

    pthread_join(hilo_servidor, NULL);

    return 0;
}
