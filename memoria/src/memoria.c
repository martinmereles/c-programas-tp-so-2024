// #include <utils/hello.h>
#include <memoria.h>

int main(int argc, char* argv[]) {
    // saludar("memoria");
    
    // Configuraciones del modulo MEMORIA.
    t_config* config = NULL;
    // Instancias de logger del modulo MEMORIA.
    t_log* logger = NULL;

    // Iniciar modulo MEMORIA.
    iniciar_modulo("MEMORIA", "../memoria/memoria.log", "../memoria/memoria.config", &logger, &config);

    // ------------------------------- SERVER -------------------------------

    // Verificar la existencia de la KEY "PUERTO_ESCUCHA" en la config.
    verificar_KEY(config, "PUERTO_ESCUCHA");
    // Iniciar socket de conexion MEMORIA.
    int fd_conexion_MEMORIA = iniciar_conexion("MEMORIA", config_get_string_value(config, "PUERTO_ESCUCHA"), &logger);

    // ------------------------------- CLIENTE -------------------------------

    // Verificar la existencia de la KEY "IP_FILESYSTEM" en la config.
    verificar_KEY(config, "IP_FILESYSTEM");
    // Verificar la existencia de la KEY "PUERTO_FILESYSTEM" en la config.
    verificar_KEY(config, "PUERTO_FILESYSTEM");
    // Iniciar cliente con FILESYSTEM.
    int fd_conexion_FILESYSTEM = iniciar_cliente("MEMORIA", "FILESYSTEM", config_get_string_value(config, "IP_FILESYSTEM"), config_get_string_value(config, "PUERTO_FILESYSTEM"), &logger);

    // Cerrar el socket de conexion del modulo MEMORIA.
    close(fd_conexion_MEMORIA);
    // Cerrar el socket de conexion del modulo FILESYSTEM.
    close(fd_conexion_FILESYSTEM);

    // Finalizar modulo MEMORIA.
    finalizar_modulo("MEMORIA", &logger, &config);
    
    return 0;
}
