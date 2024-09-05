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

    // ------------------------------- CLIENTE -------------------------------

    // Verificar la existencia de la KEY "IP_CPU" en la config.
    verificar_KEY(config, "IP_CPU");
    // Verificar la existencia de la KEY "PUERTO_CPU_DISPATCH" en la config.
    verificar_KEY(config, "PUERTO_CPU_DISPATCH");
    // Verificar la existencia de la KEY "PUERTO_CPU_INTERRUPT" en la config.
    verificar_KEY(config, "PUERTO_CPU_INTERRUPT");
    // Verificar la existencia de la KEY "IP_MEMORIA" en la config.
    verificar_KEY(config, "IP_MEMORIA");
    // Verificar la existencia de la KEY "PUERTO_MEMORIA" en la config.
    verificar_KEY(config, "PUERTO_MEMORIA");
    // Iniciar cliente con CPU (DISPATCH).
    int fd_conexion_CPU_DISPATCH = iniciar_cliente("KERNEL", "CPU_DISPATCH", config_get_string_value(config, "IP_CPU"), config_get_string_value(config, "PUERTO_CPU_DISPATCH"), &logger);
    // Iniciar cliente con CPU (INTERRUPT).
    int fd_conexion_CPU_INTERRUPT= iniciar_cliente("KERNEL", "CPU_INTERRUPT", config_get_string_value(config, "IP_CPU"), config_get_string_value(config, "PUERTO_CPU_INTERRUPT"), &logger);
    // Iniciar cliente con MEMORIA.
    int fd_conexion_MEMORIA = iniciar_cliente("KERNEL", "MEMORIA", config_get_string_value(config, "IP_MEMORIA"), config_get_string_value(config, "PUERTO_MEMORIA"), &logger);

    // Cerrar el socket de conexion del modulo CPU (DISPATCH).
    close(fd_conexion_CPU_DISPATCH);
    // Cerrar el socket de conexion del modulo CPU (INTERRUPT).
    close(fd_conexion_CPU_INTERRUPT);
    // Cerrar el socket de conexion del modulo MEMORIA.
    close(fd_conexion_MEMORIA);

    // Finalizar modulo KERNEL.
    finalizar_modulo("KERNEL", &logger, &config);

    return 0;
}