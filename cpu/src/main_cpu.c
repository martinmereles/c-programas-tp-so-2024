#include <../include/main_cpu.h>

t_log* logger;
t_config* config;
int socket_memoria;
int socket_kernel_dispatch;
int pid;
int tid;
uint32_t PC;
uint32_t AX;
uint32_t BX;
uint32_t CX;
uint32_t DX;
uint32_t EX;
uint32_t FX;
uint32_t GX;
uint32_t HX;
uint32_t BASE;
uint32_t LIMITE;

sem_t sem_execute;
bool se_ejecuto_syscall;
char* instruccion_exec;
int direccion_fisica;
t_list* interrupciones;

int main(int argc, char* argv[]) {

    sem_init(&sem_execute,0,0);
    se_ejecuto_syscall = false;
    interrupciones = list_create();
    
    
    config = iniciar_config("./cpu.config");
    char* log_level_string = config_get_string_value(config,"LOG_LEVEL");
    logger = iniciar_logger("./cpu.log", "cpu",log_level_string);

    //Inicia conexion con memoria
    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    socket_memoria = crear_conexion(ip_memoria,puerto_memoria);
    enviar_mensaje("Me conecto desde cpu!", socket_memoria);

    //Iniciar hilo servidor dispatch
    char* puerto_dispatch = config_get_string_value(config, "PUERTO_ESCUCHA_DISPATCH");
    pthread_t hilo_servidor_dispatch = iniciar_hilo_server_dispatch(puerto_dispatch);
    pthread_detach(hilo_servidor_dispatch);
    
    //Iniciar hilo servidor interrupt
    char* puerto_interrupt = config_get_string_value(config, "PUERTO_ESCUCHA_INTERRUPT");
	pthread_t hilo_servidor_interrupt = iniciar_hilo_server_interrupt(puerto_interrupt);
    pthread_detach(hilo_servidor_interrupt);

    sem_wait(&sem_execute);

    //Inicio de ciclo de instruccion
    while(1){
		fetch();
		decode();
		execute();
		check_interrupt();

        if(se_ejecuto_syscall){
            se_ejecuto_syscall = false;
            sem_wait(&sem_execute);
        }
	}
    
    //pthread_join(hilo_servidor_interrupt, NULL);

    return 0;
}
