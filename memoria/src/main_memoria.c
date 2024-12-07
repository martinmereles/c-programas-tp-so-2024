#include <../include/main_memoria.h>

t_log *logger;
t_config *config;
int socket_filesystem;
int tamanio_memoria;
char *esquema;
char *algoritmo;
t_list *lista_particiones;
t_list *procesos;
t_list *hilos;
int retardo_respuesta_cpu;
void *memoria_principal;
int socket_kernel;
char *path_instrucciones;
sem_t sem_memoria;

int main(int argc, char *argv[])
{

    // Inicializacion de variables
    config = iniciar_config("./memoria.config");
    char *log_level_string = config_get_string_value(config, "LOG_LEVEL");
    logger = iniciar_logger("./memoria.log", "memoria", log_level_string);
    sem_init(&sem_memoria, 0, 1);
    esquema = config_get_string_value(config, "ESQUEMA");
    algoritmo = config_get_string_value(config, "ALGORITMO_BUSQUEDA");
    retardo_respuesta_cpu = config_get_int_value(config, "RETARDO_RESPUESTA");
    tamanio_memoria = config_get_int_value(config, "TAM_MEMORIA");
    path_instrucciones = config_get_string_value(config, "PATH_INSTRUCCIONES");
    memoria_principal = malloc(tamanio_memoria);
    lista_particiones = list_create();
    if (string_equals_ignore_case(esquema, "FIJAS"))
    {
        char **particiones_array = config_get_array_value(config, "PARTICIONES");
        iniciar_memoria_fija(particiones_array);
    }
    else if (string_equals_ignore_case(esquema, "DINAMICAS"))
    {
        iniciar_memoria_dinamica();
    }
    procesos = list_create();
    hilos = list_create();

    // Inicia conexion con filesystem
    char *ip_filesystem = config_get_string_value(config, "IP_FILESYSTEM");
    char *puerto_filesystem = config_get_string_value(config, "PUERTO_FILESYSTEM");
    socket_filesystem = crear_conexion(ip_filesystem, puerto_filesystem);
    enviar_mensaje("Me conecto desde memoria!", socket_filesystem);

    // Iniciar hilo servidor
    char *puerto = config_get_string_value(config, "PUERTO_ESCUCHA");
    pthread_t hilo_servidor = iniciar_hilo_server_memoria(puerto);

    pthread_join(hilo_servidor, NULL);

    log_destroy(logger);
    config_destroy(config);

    return 0;
}
