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

    // Finalizar modulo FILESYSTEM.
    finalizar_modulo("FILESYSTEM", &logger, &config);

    return 0;
}
