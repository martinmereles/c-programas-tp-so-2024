// #include <utils/hello.h>
#include <filesystem.h>

int main(int argc, char* argv[]) {
    // saludar("filesystem");

    // Configuraciones del modulo FILESYSTEM.
    t_config* config = NULL;
    // Instancias de logger del modulo FILESYSTEM.
    t_log* logger = NULL;

    // Iniciar modulo FILESYSTEM.
    iniciar_modulo("FILESYSTEM", "../filesystem/filesystem.log", "../filesystem/filesystem.config", &logger, &config);

    // ------------------------------- SERVER -------------------------------
    // Verificar la existencia de la KEY "PUERTO_ESCUCHA" en la config.
    verificar_KEY(config, "PUERTO_ESCUCHA");
    // Iniciar socket de conexion FILESYSTEM.
    int fd_conexion_FILESYSTEM = iniciar_conexion("FILESYSTEM", config_get_string_value(config, "PUERTO_ESCUCHA"), &logger);

    // Cerrar el socket de conexion del modulo fd_conexion_FILESYSTEM.
    close(fd_conexion_FILESYSTEM);

    // Finalizar modulo FILESYSTEM.
    finalizar_modulo("FILESYSTEM", &logger, &config);

    return 0;
}
