// #include <utils/hello.h>
#include <kernel.h>

int main(int argc, char* argv[]) {
    // saludar("kernel");

    // Configuraciones del modulo KERNEL.
    t_config* config = NULL;
    // Instancias de logger del modulo KERNEL.
    t_log* logger = NULL;

    // Iniciar modulo KERNEL.
    iniciar_modulo("KERNEL", "../kernel/kernel.log", "../kernel/kernel.config", &logger, &config);

    // Finalizar modulo KERNEL.
    finalizar_modulo("KERNEL", &logger, &config);

    return 0;
}