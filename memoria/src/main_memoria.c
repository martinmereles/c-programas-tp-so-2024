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

int main(int argc, char *argv[])
{

    // Inicializacion de variables
    config = iniciar_config("./memoria.config");
    char *log_level_string = config_get_string_value(config, "LOG_LEVEL");
    logger = iniciar_logger("./memoria.log", "memoria", log_level_string);

    esquema = config_get_string_value(config, "ESQUEMA");
    algoritmo = config_get_string_value(config, "ALGORITMO_BUSQUEDA");
    retardo_respuesta_cpu = config_get_int_value(config, "RETARDO_RESPUESTA");
    tamanio_memoria = config_get_int_value(config, "TAM_MEMORIA");
    lista_particiones = list_create();
    if (string_equals_ignore_case(algoritmo, "FIJAS"))
    {   
        char** particiones_array = config_get_array_value(config, "PARTICIONES");

    }
    procesos = list_create();
    hilos = list_create();

    // Inicia conexion con filesystem
    char *ip_filesystem = config_get_string_value(config, "IP_FILESYSTEM");
    char *puerto_filesystem = config_get_string_value(config, "PUERTO_FILESYSTEM");
    socket_filesystem = crear_conexion(ip_filesystem, puerto_filesystem);
    enviar_mensaje("Me conecto desde memoria!", socket_filesystem);

    /*
    // INICIO PRUEBA MEMO
    crear_proceso("archivo_prueba.txt", 500, 0, 1);
    //obtener_contexto(1, 0, 8);
    // FIN PRUEBA MEMO

    // INICIO PRUEBA FS
    t_paquete *a = crear_paquete();
    agregar_a_paquete(a, "DUMP_MEMORY", 12);
    agregar_a_paquete(a, "nombre-de-archivo", 18);
    int numero = 69;
    agregar_a_paquete(a, string_itoa(numero), 3);
    agregar_a_paquete(a, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEF", 69);
    enviar_paquete(a, socket_filesystem);
    // FIN PRUEBA FS
    */


    // Iniciar hilo servidor
    char *puerto = config_get_string_value(config, "PUERTO_ESCUCHA");
    pthread_t hilo_servidor = iniciar_hilo_server_memoria(puerto);

    pthread_join(hilo_servidor, NULL);

    return 0;
}
