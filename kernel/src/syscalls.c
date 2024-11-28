#include <../include/syscalls.h>

void sys_crear_proceso(char *archivo, int tamanio, int prioridad, int pid, int tid)
{

    crear_proceso(archivo, tamanio, prioridad);
    log_info(logger, "SE EJECUTO LA SYSCALL PROCESS_CREATE");
    dispatcher(tid, pid);
}

void sys_process_exit(int pid, int tid)
{

    finalizar_proceso(pid);
    log_info(logger, "SE EJECUTO LA SYSCALL PROCESS_EXIT PARA EL PROCESO %d", pid);
    sem_post(&sem_contador_ready);
    dispatcher(tid, pid);
}

void sys_thread_create(char *archivo_ps, int prioridad, int ppid, int tid)
{

    t_tcb *new_thread = crear_hilo(prioridad, ppid, tid);
    sem_wait(&sem_mutex_colas);
    int index = get_index(new_thread->prioridad);
    list_add_in_index(QUEUE_READY, index, new_thread);
    sem_post(&sem_mutex_colas);
    log_info(logger, "SE EJECUTO LA SYSCALL PROCESS_CREATE");
    sem_post(&sem_contador_ready);
    dispatcher(tid, ppid);
}

void sys_thread_join(int tid_join, int ppid, int tid)
{

    bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(ppid, tid_join, elemento);
    }
    t_tcb *tcb_encontrado_exec = list_find(QUEUE_EXEC, _es_tcb_buscado);
    t_tcb *tcb_encontrado_blocked = list_find(QUEUE_BLOCKED, _es_tcb_buscado);

    if (tcb_encontrado_blocked == NULL && tcb_encontrado_exec == NULL)
    {
        log_info(logger, "Hilo <%d : %d> no existe", tid_join, ppid);
        dispatcher(tid, ppid);
    }
    else
    {

        t_hilo_join *hilo_a_bloquear = malloc(sizeof(t_hilo_join));
        hilo_a_bloquear->ppid = ppid;
        hilo_a_bloquear->tid = tid;
        hilo_a_bloquear->tid_join = tid_join;
        t_tcb *tcb_encontrado = NULL;
        bool _es_tcb_buscado_existe(void *elemento)
        {
            return es_tcb_buscado(ppid, tid, elemento);
        }
        tcb_encontrado = list_remove_by_condition(QUEUE_EXEC, _es_tcb_buscado_existe);
        // chequeamos que exista el hilo en la cola
        if (tcb_encontrado == NULL)
        {
            log_info(logger, "Hilo no encontrado");
            return;
        }
        else
        {
            // tcb_encontrado->estado = BLOCKED;
            list_add(QUEUE_BLOCKED, tcb_encontrado);
            list_add(TCB_BLOQUEADOS, hilo_a_bloquear);
        }
        log_info(logger, "SE EJECUTO LA SYSCALL THREAD_JOIN");
        sem_post(&sem_contador_ready);
    }
}

void sys_thread_cancel(int tid_cancel, int ppid, int tid)
{

    bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(ppid, tid_cancel, elemento);
    }
    t_tcb *tcb_encontrado_blocked = list_find(QUEUE_BLOCKED, _es_tcb_buscado);
    t_tcb *tcb_encontrado_ready = list_find(QUEUE_READY, _es_tcb_buscado);

    if (tcb_encontrado_blocked != NULL)
    {
        finalizar_hilo(tcb_encontrado_blocked->ppid, tid_cancel; QUEUE_BLOCKED);
    }
    else if (tcb_encontrado_ready != NULL)
    {
        finalizar_hilo(tcb_encontrado_ready->ppid, tid_cancel; QUEUE_READY);
    }
    dispatcher(tid, ppid);
}

void sys_thread_exit(int pid, int tid)
{
    finalizar_hilo(pid, tid, QUEUE_EXEC);
    sem_post(&sem_corto_plazo);
}

void sys_mutex_create(char *nombre, int pid, int tid)
{
    t_mutex *nuevo_mutex = malloc(sizeof(t_mutex));
    nuevo_mutex->pid_asignado = pid;
    nuevo_mutex->tid = NULL;
    nuevo_mutex->nombre = nombre;
    nuevo_mutex->bloqueados = list_create();
    nuevo_mutex->valor = 1;
    bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(pid, elemento);
    }
    t_pcb *pcb_encontrado = list_find(PCB_EN_CICLO, _es_pcb_buscado);
    list_add(pcb_encontrado->mutex, nuevo_mutex);
    dispatcher(tid, pid);
}

void sys_mutex_lock(char *nombre, int pid, int tid)
{
    bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(pid, elemento);
    }
    t_pcb *pcb_encontrado = list_find(PCB_EN_CICLO, _es_pcb_buscado);
    bool _es_mutex_buscado(void *elemento)
    {
        return es_mutex_buscado(char *nombre, elemento);
    }
    t_mutex *mutex_encontrado = list_find(pcb_encontrado->mutex, _es_mutex_buscado);
    if (mutex_encontrado != NULL)
    {
        if (mutex_encontrado->valor > 0)
        {
            mutex_encontrado->valor--;
            mutex_encontrado->tid_asignado = tid;
            dispatcher(tid, pid);
        }
        else
        {
            t_tcb *tcb_encontrado = list_remove(QUEUE_EXEC, 0);
            list_add(QUEUE_BLOCKED, tcb_encontrado);
            list_add(mutex_encontrado->bloqueados, tcb_encontrado->tid);
            sem_post(&sem_corto_plazo);
        }
    }
    else
    {
        finalizar_hilo(pid, tid, QUEUE_EXEC);
    }
}

void sys_mutex_unlock(char *nombre, int pid, int tid)
{
    bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(pid, elemento);
    }
    t_pcb *pcb_encontrado = list_find(PCB_EN_CICLO, _es_pcb_buscado);
    bool _es_mutex_buscado(void *elemento)
    {
        return es_mutex_buscado(char *nombre, elemento);
    }
    t_mutex *mutex_encontrado = list_find(pcb_encontrado->mutex, _es_mutex_buscado);
    if (mutex_encontrado != NULL)
    {
        if (mutex_encontrado->tid_asignado == tid)
        {
            mutex_encontrado->valor++;
            if (mutex_encontrado->valor == 1)
            {
                mutex_encontrado->tid_asignado = NULL;
                dispatcher(tid, pid);
            }
            else if (mutex_encontrado->valor < 1)
            {
                int tid_a_desbloquear = list_remove(mutex_encontrado->bloqueados, 0);
                mutex_encontrado->tid_asignado = tid_a_desbloquear;
                bool _es_tcb_buscado(void *elemento)
                {
                    return es_tcb_buscado(pid, tid_a_desbloquear, elemento);
                }
                t_tcb *tcb_encontrado_blocked = list_find(QUEUE_BLOCKED, _es_tcb_buscado);
                list_remove_element(QUEUE_BLOCKED, tcb_encontrado_blocked);
                asignar_a_ready(tcb_encontrado_blocked);
            }

            dispatcher(tid, pid);
        }
    }
    else
    {
        finalizar_hilo(pid, tid, QUEUE_EXEC);
    }
}
bool es_mutex_buscado(char *nombre, void *elemento)
{
    t_mutex *aux = malloc(sizeof(t_mutex));
    aux = elemento;
    bool aux2 = (strcmp(aux->nombre, nombre) == 0);
    return (aux2);
}

void asignar_a_ready(t_tcb *tcb_a_asignar)
{

    if (strcmp(algoritmo_planificacion, "FIFO") == 0)
    {

        list_add(QUEUE_READY, tcb_a_asignar);
    }
    else if (strcmp(algoritmo_planificacion, "PRIORIDADES") == 0 || strcmp(algoritmo_planificacion, 'CMN') == 0)
    {

        int index = get_index(tcb_a_asignar->prioridad);

        list_add_in_index(QUEUE_READY, index, tcb_a_asignar);
    }
}
