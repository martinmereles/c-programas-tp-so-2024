#include <../include/auxiliares_kernel.h>

void crear_proceso (char* archivo, int tamanio, int prioridad){
    //creo estructuras y reservo memoria
    t_pcb* pcb = malloc(sizeof(t_pcb));
    pcb->tids = list_create();
    pcb->mutex = list_create();

    t_tcb* tcb = malloc(sizeof(t_tcb));
    
    //inicializo las estructuras
    pcb->estado = NEW;
    pcb->pid = contador_pid;
    contador_pid ++;
    list_add(pcb->tids, 0);
    
    tcb->estado = NEW;
    tcb->ppid = contador_pid;
    tcb->tid = 0;
    tcb->prioridad = prioridad;
    
    list_add (QUEUE_NEW, tcb); // consultar si va aca o en otro paso, o como se encola

    
    //envio mensaje a memoria (podria ir en el planificador de largo, consultar)
    /*char *mensaje = string_new();
    string_append(&mensaje, archivo);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tamanio));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pcb->pid));
    
    enviar_mensaje(mensaje, socket_memoria);
    //TODO recibir mensaje de memoria

    bool cola_vacia = 1;

    if (cola_vacia) {
        pcb->estado =READY;
        tcb->estado = READY;
        list_remove
        return;
    }
    else{
        
        //TODO bloquer proceso a la espera de espacio en la memoria
    }
    */



    //




    //TODO signal Semaforo

}

