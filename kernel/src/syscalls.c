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
    //crear_hilo()

}

void sys_thread_join (int tid) {

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