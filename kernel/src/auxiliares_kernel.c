#include <../include/auxiliares_kernel.h>

//Planificador de Largo PLazo

void crear_proceso (char* archivo, int tamanio, int prioridad){
    //creo estructuras y reservo memoria
    t_pcb* pcb = malloc(sizeof(t_pcb));
    pcb->tids = list_create();
    pcb->mutex = list_create();


    //inicializo las estructuras pcb
    pcb->estado = NEW;
    pcb->pid = contador_pid;
    contador_pid ++;
    pcb->prioridad_hilo_main = prioridad;
    pcb->archivo = archivo;
    pcb->tamanio = tamanio;
    
    list_add (QUEUE_NEW, pcb);


}

void finalizar_proceso (int pid) {

       bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(pid, elemento);
    }
    t_pcb* pcb_encontrado = list_find(PCB_EN_CICLO, _es_pcb_buscado);
    pcb_encontrado->estado = EXIT;
    int tid_a_remover;

    for (int i = 0;  i < list_size(pcb_encontrado->tids); i++)
    {
       tid_a_remover = list_get(pcb_encontrado->tids, i); // d finalizar_hilo (int pid, int tid, t_list* cola)
        finalizar_hilo (pcb_encontrado->pid, tid_a_remover, QUEUE_READY);
        finalizar_hilo (pcb_encontrado->pid, tid_a_remover, QUEUE_BLOCKED);
        finalizar_hilo (pcb_encontrado->pid, tid_a_remover, QUEUE_EXEC);
    }
     char* mensaje = string_new ();
        string_append(&mensaje,"PROCESS_EXIT");
        string_append(&mensaje, string_itoa(pcb_encontrado->pid));
        enviar_mensaje(mensaje, socket_memoria);
    //recibir mensaje de confirmacion de memoria


}
// funcion que busca pcb segun pid
bool es_pcb_buscado(int pid_buscado, void *elemento)
{
    t_pcb* aux = malloc(sizeof(t_pcb));
    aux = elemento;
    bool aux2 = (aux->pid == pid_buscado);
    return (aux2);
}


t_tcb* crear_hilo (int prioridad, int ppid, int tid) {
    
    t_tcb* tcb = malloc(sizeof(t_tcb));
    //inicializo
    tcb->estado = READY;
    tcb->ppid = ppid;
    tcb->tid = tid;
    tcb->prioridad = prioridad;

    return tcb;
}

void planificador_largo_plazo (){
    while (true)
    {
        sem_wait(&sem_largo_plazo);
        
        int tamanio_cola = list_size(QUEUE_NEW);

        for (int i = 0; i < tamanio_cola; i++)
        {
            t_pcb* pcb = list_get(QUEUE_NEW, i);
            //armo mensaje para memoria
            char* mensaje = string_new ();
            string_append(&mensaje,"PROCESS_CREATE ");
            string_append(&mensaje, pcb->archivo);
            string_append(&mensaje," ");
            string_append(&mensaje, string_itoa(pcb->tamanio));
            string_append(&mensaje," ");
            string_append(&mensaje, string_itoa(pcb->prioridad_hilo_main));
            string_append(&mensaje," ");
            string_append(&mensaje, string_itoa(pcb->pid));
            //envio mensaje a memoria
            enviar_mensaje(mensaje, socket_memoria);
            //TODO recibir respuesta de memoria
            bool hay_espacio = true; // validar segun respuesta de memoria
            if (hay_espacio)
            {
             
               t_tcb* nuevo_hilo = crear_hilo(pcb->prioridad_hilo_main, pcb->pid, 0);
               list_add(QUEUE_READY, nuevo_hilo);
               list_add(PCB_EN_CICLO, list_remove(QUEUE_NEW, 0));
            }
            else {
                break;
            }
        }
        
        
    }
    
}

void finalizar_hilo (int pid, int tid, t_list* cola) {
//funcion booleana para buscar tcb en colas
bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(pid, tid, elemento);
    }
    t_tcb* tcb_encontrado = NULL;
    tcb_encontrado = list_remove_by_condition(cola, _es_tcb_buscado);
   //chequeamos que exista el hilo en la cola
   if (tcb_encontrado == NULL){
     log_info(logger, "Hilo no encontrado");
     return;   
    }
    else {
    tcb_encontrado->estado = EXIT;
    list_add (QUEUE_EXIT, tcb_encontrado);
    
    
    //enviamos mensaje a memoria para finalizar hilo
     char* mensaje = string_new ();
        string_append(&mensaje,"FINALIZAR_HILO ");
        string_append(&mensaje, string_itoa(tcb_encontrado->ppid));
        string_append(&mensaje," ");
        string_append(&mensaje, string_itoa(tcb_encontrado->tid));

        enviar_mensaje(mensaje, socket_memoria);
        //recibir mensaje de confirmacion
        log_info(logger, "< %i : %i> finaliza el hilo", tcb_encontrado->ppid, tcb_encontrado->tid);
    }
}

bool es_tcb_buscado(int pid_buscado, int tid_buscado, void *elemento)
{
    t_tcb* aux = malloc(sizeof(t_pcb));
    aux = elemento;
    bool aux2 = (aux->tid == tid_buscado && aux->ppid == pid_buscado);
    return (aux2);
}


//Planificador de corto plazo

void planificador_corto_plazo(){

    int socket_cpu_dispatch = atoi(config_get_string_value(config, "PUERTO_CPU_DISPATCH")); 
    int socket_cpu_interrupt = atoi(config_get_string_value(config, "PUERTO_CPU_INTERRUPT"));

    char* algoritmo = config_get_string_value(config, "ALGORITMO_PLANIFICACION");

    
    if(!strcmp(algoritmo,"FIFO")){
        ejecutar_fifo(socket_cpu_dispatch);
    }else if(!strcmp(algoritmo,"PRIORIDADES")){
        ejecutar_prioridades(socket_cpu_dispatch, socket_cpu_interrupt);
    }else if(!strcmp(algoritmo,"CMN")){
        ejecutar_cmn(socket_cpu_dispatch, socket_cpu_interrupt);
    }
    config_destroy(config);

}

void ejecutar_fifo(socket_cpu_dispatch){
        while(1){        

        t_tcb* tcb_a_enviar = malloc(sizeof(t_tcb));
        sem_wait(&planificador_corto_plazo); // validar que no sean necesarios mas semaforos
        tcb_a_enviar = list_remove(QUEUE_READY, 0);
        list_add(QUEUE_EXEC, tcb_a_enviar);
        sem_post(&planificador_corto_plazo);
        log_info(logger, "TID: %d - Estado Anterior: READY - Estado Actual: RUNNING", tcb_a_enviar->tid);
        
    }
}

void ejecutar_prioridades(socket_cpu_dispatch, socket_cpu_interrupt){

}
void ejecutar_cmn(socket_cpu_dispatch, socket_cpu_interrupt){

}
