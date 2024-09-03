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

    // Finalizar modulo MEMORIA.
    finalizar_modulo("MEMORIA", &logger, &config);
    
    return 0;
}
