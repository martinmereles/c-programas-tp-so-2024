#include <../include/syscalls.h>

void sys_crear_proceso(char *archivo, int tamanio, int prioridad, int pid, int tid)
{

    crear_proceso(archivo, tamanio, prioridad);
    sem_post(&sem_largo_plazo);
    dispatcher(tid, pid);
}

void sys_process_exit(int pid, int tid)
{

    finalizar_proceso(pid);
    sem_post(&sem_corto_plazo);
    sem_post(&sem_largo_plazo);
}

void sys_thread_create(char *archivo_ps, int prioridad, int ppid, int tid)
{
    bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(ppid, elemento);
    }
    t_pcb *pcb_encontrado = list_find(PCB_EN_CICLO, _es_pcb_buscado);

    t_tcb *new_thread = crear_hilo(archivo_ps, prioridad, ppid, list_size(pcb_encontrado->tids));
    sem_wait(&sem_mutex_colas);
    if (strcmp(algoritmo_planificacion, "FIFO") == 0)
    {

        list_add(QUEUE_READY, new_thread);
    }
    else if (strcmp(algoritmo_planificacion, "PRIORIDADES") == 0 || strcmp(algoritmo_planificacion, "CMN") == 0)
    {

        int index = get_index(new_thread->prioridad);

        list_add_in_index(QUEUE_READY, index, new_thread);
    }
    sem_post(&sem_mutex_colas);
    sem_post(&sem_contador_ready);
    dispatcher(tid, ppid);
    log_info(logger, "## (%d:%d) Se crea el Hilo - Estado: READY", ppid, tid);
}

void sys_thread_join(int tid_join, int ppid, int tid)
{

    bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(ppid, tid_join, elemento);
    }
    t_tcb *tcb_encontrado_ready = list_find(QUEUE_READY, _es_tcb_buscado);
    t_tcb *tcb_encontrado_blocked = list_find(QUEUE_BLOCKED, _es_tcb_buscado);

    if (tcb_encontrado_blocked == NULL && tcb_encontrado_ready == NULL)
    {
        log_info(logger, "## (%d:%d) Hilo no existe", ppid, tid_join);
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
        sem_wait(&sem_mutex_colas);
        tcb_encontrado = list_remove_by_condition(QUEUE_EXEC, _es_tcb_buscado_existe);

        // chequeamos que exista el hilo en la cola
        if (tcb_encontrado == NULL)
        {
            log_info(logger, "## (%d:%d) Hilo no existe", ppid, tid_join);
            return;
        }
        else
        {
            // tcb_encontrado->estado = BLOCKED;
            
            list_add(QUEUE_BLOCKED, tcb_encontrado);
            sem_wait(&sem_tcb_bloqueados);
            list_add(TCB_BLOQUEADOS, hilo_a_bloquear);
            sem_post(&sem_tcb_bloqueados);
            log_info(logger, "## (%d:%d) - Bloqueado por: PTHREAD_JOIN", ppid, tid);
        }
        sem_post(&sem_mutex_colas);
        sem_post(&sem_corto_plazo);
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
        finalizar_hilo(tcb_encontrado_blocked->ppid, tid_cancel, QUEUE_BLOCKED);
        log_info(logger, "## (%d:%d) - Finaliza el hilo", ppid, tid);
        sem_post(&sem_largo_plazo);
    }
    else if (tcb_encontrado_ready != NULL)
    {
        
        finalizar_hilo(tcb_encontrado_ready->ppid, tid_cancel, QUEUE_READY);
        log_info(logger, "## (%d:%d) - Finaliza el hilo", ppid, tid);
        sem_post(&sem_largo_plazo);
        
    }
    dispatcher(tid, ppid);
}

void sys_thread_exit(int pid, int tid)
{
    finalizar_hilo(pid, tid, QUEUE_EXEC);
    sem_post(&sem_corto_plazo);
    log_info(logger, "## (%d:%d) - Finaliza el hilo", pid, tid);
}

void sys_mutex_create(char *nombre, int pid, int tid)
{
    t_mutex *nuevo_mutex = malloc(sizeof(t_mutex));
    nuevo_mutex->pid_asignado = pid;
    nuevo_mutex->tid_asignado = NULL;
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
        return es_mutex_buscado(nombre, elemento);
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
            mutex_encontrado->valor--;
            sem_wait(&sem_mutex_colas);
            t_tcb *tcb_encontrado = list_remove(QUEUE_EXEC, 0);
            list_add(QUEUE_BLOCKED, tcb_encontrado);
            sem_post(&sem_mutex_colas);
            list_add(mutex_encontrado->bloqueados, tcb_encontrado->tid);
            log_info(logger, "## (%d:%d) - Bloqueado por: MUTEX", pid, tid);
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
        return es_mutex_buscado(nombre, elemento);
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
                        }
            else if (mutex_encontrado->valor < 1)
            {
                int tid_a_desbloquear = list_remove(mutex_encontrado->bloqueados, 0);
                mutex_encontrado->tid_asignado = tid_a_desbloquear;
                bool _es_tcb_buscado(void *elemento)
                {
                    return es_tcb_buscado(pid, tid_a_desbloquear, elemento);
                }
                sem_wait(&sem_mutex_colas);
                t_tcb *tcb_encontrado_blocked = list_find(QUEUE_BLOCKED, _es_tcb_buscado);
                list_remove_element(QUEUE_BLOCKED, tcb_encontrado_blocked);
                asignar_a_ready(tcb_encontrado_blocked);
                sem_post(&sem_mutex_colas);
                sem_post(&sem_contador_ready);
            }

            dispatcher(tid, pid);
        }
    }
    else
    {
        finalizar_hilo(pid, tid, QUEUE_EXEC);
    }
}

void sys_dump_memory(int pid, int tid)
{
    // Bloquear hilo
    t_tcb *tcb_encontrado = list_remove(QUEUE_EXEC, 0);
    list_add(QUEUE_BLOCKED, tcb_encontrado);

    char *ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    char *puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    int socket_memoria_dump = crear_conexion(ip_memoria, puerto_memoria);


    // Envio mensaje a memoria
    char *mensaje = string_new();
    string_append(&mensaje, "DUMP_MEMORY");
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje, socket_memoria_dump);
    sem_post(&sem_corto_plazo);

    // Creo hilo de escucha
    pthread_t hilo_respuesta_memoria;
    pthread_create(&hilo_respuesta_memoria,
                   NULL,
                   esperar_respuesta_dump_memory,
                   socket_memoria_dump);
    pthread_detach(hilo_respuesta_memoria);
    
}

void sys_io(int tiempo, int pid, int tid)
{
    bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(pid, tid, elemento);
    }
    t_tcb *tcb_encontrado;
    sem_wait(&sem_mutex_colas);
    tcb_encontrado = list_remove_by_condition(QUEUE_EXEC, _es_tcb_buscado);
    char *mensaje = string_new();
    string_append(&mensaje, string_itoa(tiempo));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    list_add(QUEUE_BLOCKED, tcb_encontrado);
    log_info(logger, "## (%d:%d) - Bloqueado por: IO", pid, tid);
    sem_post(&sem_mutex_colas);

    pthread_t hilo_atencion_io;
    pthread_create(&hilo_atencion_io,
                   NULL,
                   atender_io,
                   mensaje);
    pthread_detach(hilo_atencion_io);
    sem_post(&sem_corto_plazo);
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
    else if (strcmp(algoritmo_planificacion, "PRIORIDADES") == 0 || strcmp(algoritmo_planificacion, "CMN") == 0)
    {

        int index = get_index(tcb_a_asignar->prioridad);

        list_add_in_index(QUEUE_READY, index, tcb_a_asignar);
    }
}

void atender_io(char *mensaje)
{
    char **parametros = string_split(mensaje, " ");

    int tiempo_miliseconds = atoi(parametros[0]) * 1000;
    int pid = atoi(parametros[1]);
    int tid = atoi(parametros[2]);
    usleep(tiempo_miliseconds);
    bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(pid, tid, elemento);
    }
    t_tcb *tcb_encontrado;
    sem_wait(&sem_mutex_colas);
    tcb_encontrado = list_remove_by_condition(QUEUE_BLOCKED, _es_tcb_buscado);
    asignar_a_ready(tcb_encontrado);
    sem_post(&sem_mutex_colas);
    sem_post(&sem_contador_ready);
    log_info(logger, "## (%d:%d) finalizó IO y pasa a READY", pid, tid);
}