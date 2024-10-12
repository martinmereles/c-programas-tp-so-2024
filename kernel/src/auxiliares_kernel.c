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
    
    list_add (QUEUE_NEW, pcb)


}

void finalizar_proceso (t_pcb* pcb;) {
    //Cambio de estado el pcb del proceso
    pcb->estado = EXIT;
    //es necesario validar que los hilos esten finalizados? consultar

       bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(atoi(pid), elemento);
    }
    t_pcb* pcb_encontrado;
    pcb_encontrado = list_remove_by_condition(QUEUE_BLOCKED, _es_pcb_buscado);
    list_add (QUEUE_EXIT, pcb_encontrado);
    


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

        for (int i = 0; i < tamanio_cola i++)
        {
            /* code */
        }
        
        
    }
    
}