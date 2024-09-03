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

    // Finalizar modulo CPU.
    finalizar_modulo("CPU", &logger, &config);

    return 0;
}
