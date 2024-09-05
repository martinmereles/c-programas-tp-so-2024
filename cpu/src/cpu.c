// #include <utils/hello.h>
#include <cpu.h>

int main(int argc, char* argv[]) {
    // saludar("cpu");

    // Configuraciones del modulo CPU.
    t_config* config = NULL;
    // Instancias de logger del modulo CPU.
    t_log* logger = NULL;

    // Iniciar modulo CPU.
    iniciar_modulo("CPU", "../cpu/cpu.log", "../cpu/cpu.config", &logger, &config);

    // ------------------------------- SERVER -------------------------------

    // Verificar la existencia de la KEY "PUERTO_ESCUCHA_DISPATCH" en la config.
    verificar_KEY(config, "PUERTO_ESCUCHA_DISPATCH");
    // Verificar la existencia de la KEY "PUERTO_ESCUCHA_INTERRUPT" en la config.
    verificar_KEY(config, "PUERTO_ESCUCHA_INTERRUPT");
    // Iniciar socket de conexion CPU-DISPATCH.
    int fd_conexion_CPU_DISPATCH = iniciar_conexion("CPU-DISPATCH", config_get_string_value(config, "PUERTO_ESCUCHA_DISPATCH"), &logger);
    // Iniciar socket de conexion CPU-INTERRUPT.
    int fd_conexion_CPU_INTERRUPT = iniciar_conexion("CPU-INTERRUPT", config_get_string_value(config, "PUERTO_ESCUCHA_INTERRUPT"), &logger);

    // ------------------------------- CLIENTE -------------------------------

    // Verificar la existencia de la KEY "IP_MEMORIA" en la config.
    verificar_KEY(config, "IP_MEMORIA");
    // Verificar la existencia de la KEY "PUERTO_MEMORIA" en la config.
    verificar_KEY(config, "PUERTO_MEMORIA");
    // Iniciar cliente con MEMORIA.
    int fd_conexion_MEMORIA = iniciar_cliente("CPU", "MEMORIA", config_get_string_value(config, "IP_MEMORIA"), config_get_string_value(config, "PUERTO_MEMORIA"), &logger);

    // Cerrar el socket de conexion del modulo CPU (DISPATCH).
    close(fd_conexion_CPU_DISPATCH);
    // Cerrar el socket de conexion del modulo CPU (INTERRUPT).
    close(fd_conexion_CPU_INTERRUPT);
    // Cerrar el socket de conexion del modulo MEMORIA.
    close(fd_conexion_MEMORIA);

    // Finalizar modulo CPU.
    finalizar_modulo("CPU", &logger, &config);

    return 0;
}
