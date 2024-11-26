#include <../include/syscalls.h>
#include <../include/auxiliares_kernel.h>


void sys_crear_proceso (char* archivo, int tamanio, int prioridad){
    crear_proceso(archivo, tamanio, prioridad);
    log_info(logger, "SE EJECUTO LA SYSCALL PROCESS_CREATE");
}

void sys_process_exit (int pid, int tid) {
    if (tid == 0){
        
   finalizar_proceso(pid);
   log_info(logger, "SE EJECUTO LA SYSCALL PROCESS_EXIT PARA EL PROCESO %d", pid );
    }


}

void sys_thread_create(char* archivo_ps, int prioridad, int ppid, int tid) {

    t_tcb* new_thread = crear_hilo(prioridad, ppid, tid);
    sem_wait(&sem_mutex_colas);
    int index = get_index(new_thread->prioridad);
    list_add_in_index(QUEUE_READY, index, new_thread);
    sem_post(&sem_mutex_colas);
    log_info(logger, "SE EJECUTO LA SYSCALL PROCESS_CREATE");

}

void sys_thread_join (int tid_join, int ppid, int tid) {

    t_hilo_join* hilo_a_bloquear = malloc(sizeof(t_hilo_join));
    hilo_a_bloquear->ppid = ppid;
    hilo_a_bloquear->tid = tid;
    hilo_a_bloquear->tid_join =tid_join;
     t_tcb *tcb_encontrado = NULL;
     bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(ppid, tid, elemento);
    }
    tcb_encontrado = list_remove_by_condition(QUEUE_EXEC, _es_tcb_buscado);
    // chequeamos que exista el hilo en la cola
    if (tcb_encontrado == NULL)
    {
        log_info(logger, "Hilo no encontrado");
        return;
    }
    else
    {
        tcb_encontrado->estado = BLOCKED;
        list_add(QUEUE_BLOCKED, tcb_encontrado);
        list_add(TCB_BLOQUEADOS, hilo_a_bloquear);
    }
        log_info(logger, "SE EJECUTO LA SYSCALL THREAD_JOIN");


}

void sys_thread_cancel (int tid) {

    

}

void sys_thread_exit (int pid, int tid) {
    finalizar_hilo( pid, tid, QUEUE_EXEC);

}

void sys_mutex_create () {

}

void sys_mutex_lock () {
}

void sys_mutex_unlock () {
}