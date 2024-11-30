#include <../include/auxiliares_kernel.h>

// Planificador de Largo PLazo

void crear_proceso(char *archivo, int tamanio, int prioridad)
{
    // creo estructuras y reservo memoria
    t_pcb *pcb = malloc(sizeof(t_pcb));
    pcb->tids = list_create();
    pcb->mutex = list_create();

    // inicializo las estructuras pcb
    // pcb->estado = NEW;
    pcb->pid = contador_pid;
    contador_pid++;
    pcb->prioridad_hilo_main = prioridad;
    pcb->archivo = archivo;
    pcb->tamanio = tamanio;

    list_add(QUEUE_NEW, pcb);
    log_info(logger, "## (%d:0) - Se crea el proceso - Estado: NEW", pcb->pid);
}

void finalizar_proceso(int pid)
{

    bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(pid, elemento);
    }
    t_pcb *pcb_encontrado = list_find(PCB_EN_CICLO, _es_pcb_buscado);
    // pcb_encontrado->estado = EXIT;
    int tid_a_remover;

    for (int i = 0; i < list_size(pcb_encontrado->tids); i++)
    {
        tid_a_remover = list_get(pcb_encontrado->tids, i); // d finalizar_hilo (int pid, int tid, t_list* cola)
        bool resultado = finalizar_hilo(pcb_encontrado->pid, tid_a_remover, QUEUE_READY);
        if (resultado)
        {
            sem_wait(&sem_contador_ready);
        }
        finalizar_hilo(pcb_encontrado->pid, tid_a_remover, QUEUE_BLOCKED);
        finalizar_hilo(pcb_encontrado->pid, tid_a_remover, QUEUE_EXEC);
    }
    char *mensaje = string_new();
    string_append(&mensaje, "PROCESS_EXIT ");
    string_append(&mensaje, string_itoa(pcb_encontrado->pid));
    enviar_mensaje(mensaje, socket_memoria);
    log_info(logger, "## Finaliza el proceso %d", pid);
}
// funcion que busca pcb segun pid
bool es_pcb_buscado(int pid_buscado, void *elemento)
{
    t_pcb *aux = malloc(sizeof(t_pcb));
    aux = elemento;
    bool aux2 = (aux->pid == pid_buscado);
    return (aux2);
}

t_tcb *crear_hilo(char *archivo, int prioridad, int ppid, int tid)
{
    bool _es_pcb_buscado(void *elemento)
    {
        return es_pcb_buscado(ppid, elemento);
    }
    t_pcb *pcb_encontrado;
    if (tid == 0)
    {
        pcb_encontrado = list_find(QUEUE_NEW, _es_pcb_buscado);
    }
    else
    {
        pcb_encontrado = list_find(PCB_EN_CICLO, _es_pcb_buscado);
    }
    t_tcb *tcb = malloc(sizeof(t_tcb));
    tcb->ppid = ppid;
    tcb->tid = tid;
    tcb->prioridad = prioridad;
    list_add(pcb_encontrado->tids, tcb->tid);

    char *mensaje = string_new();
    string_append(&mensaje, "THREAD_CREATE ");
    string_append(&mensaje, archivo);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(prioridad));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(ppid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje, socket_memoria);

    return tcb;
}

void planificador_largo_plazo()
{
    while (true)
    {
        sem_wait(&sem_largo_plazo);

        int tamanio_cola = list_size(QUEUE_NEW);

        sem_wait(&sem_mutex_colas);
        for (int i = 0; i < tamanio_cola; i++)
        {
            t_pcb *pcb = list_get(QUEUE_NEW, i);
            // armo mensaje para memoria
            char *mensaje = string_new();
            string_append(&mensaje, "PROCESS_CREATE ");
            string_append(&mensaje, pcb->archivo);
            string_append(&mensaje, " ");
            string_append(&mensaje, string_itoa(pcb->tamanio));
            string_append(&mensaje, " ");
            string_append(&mensaje, string_itoa(pcb->prioridad_hilo_main));
            string_append(&mensaje, " ");
            string_append(&mensaje, string_itoa(pcb->pid));
            // envio mensaje a memoria
            enviar_mensaje(mensaje, socket_memoria);

            char *mensaje_resultado = recibir_desde_memoria(socket_memoria);

            // validar segun respuesta de memoria
            if (string_starts_with(mensaje_resultado, "PROCESS_CREATE_OK"))
            {
                t_tcb *nuevo_hilo = malloc(sizeof(t_tcb));
                nuevo_hilo->ppid = pcb->pid;
                nuevo_hilo->tid = 0;
                nuevo_hilo->prioridad = pcb->prioridad_hilo_main;
                list_add(pcb->tids, nuevo_hilo->tid);

                if (strcmp(algoritmo_planificacion, "FIFO") == 0)
                {
                    list_add(QUEUE_READY, nuevo_hilo);

                    list_add(PCB_EN_CICLO, list_remove(QUEUE_NEW, 0));
                    sem_post(&sem_contador_ready);
                }
                else if (strcmp(algoritmo_planificacion, "PRIORIDADES") == 0 || strcmp(algoritmo_planificacion, "CMN") == 0)
                {
                    int index = get_index(nuevo_hilo->prioridad);

                    list_add_in_index(QUEUE_READY, index, nuevo_hilo);
                }
            }
            else if (strcmp(mensaje_resultado, "PROCESS_CREATE_FAIL") == 0)
            {
                break;
            }
        }
        sem_post(&sem_mutex_colas);
    }
}

bool finalizar_hilo(int pid, int tid, t_list *cola)
{
    // funcion booleana para buscar tcb en colas
    bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(pid, tid, elemento);
    }
    t_tcb *tcb_encontrado = NULL;
    sem_wait(&sem_mutex_colas);
    tcb_encontrado = list_remove_by_condition(cola, _es_tcb_buscado);
    bool validacion;
    // chequeamos que exista el hilo en la cola
    if (tcb_encontrado == NULL)
    {
        validacion = false;
    }
    else
    {

        // tcb_encontrado->estado = EXIT;
        list_add(QUEUE_EXIT, tcb_encontrado);

        // enviamos mensaje a memoria para finalizar hilo
        char *mensaje = string_new();
        string_append(&mensaje, "FINALIZAR_HILO ");
        string_append(&mensaje, string_itoa(tcb_encontrado->ppid));
        string_append(&mensaje, " ");
        string_append(&mensaje, string_itoa(tcb_encontrado->tid));

        enviar_mensaje(mensaje, socket_memoria);
        // recibir mensaje de confirmacion
        desbloquear_hilos_join(tcb_encontrado->tid, tcb_encontrado->ppid);
        validacion = true;
    }
    sem_post(&sem_mutex_colas);
    return validacion;
}

bool es_tcb_buscado(int pid_buscado, int tid_buscado, void *elemento)
{
    t_tcb *aux = malloc(sizeof(t_tcb));
    aux = elemento;
    bool aux2 = (aux->tid == tid_buscado && aux->ppid == pid_buscado);
    return (aux2);
}

// Planificador de corto plazo

void planificador_corto_plazo()
{

    if (!strcmp(algoritmo_planificacion, "FIFO"))
    {
        ejecutar_fifo();
    }
    else if (!strcmp(algoritmo_planificacion, "PRIORIDADES"))
    {
        ejecutar_prioridades();
    }
    else if (!strcmp(algoritmo_planificacion, "CMN"))
    {
        ejecutar_cmn();
    }
    config_destroy(config);
}

void ejecutar_fifo()
{
    while (1)
    {

        sem_wait(&sem_contador_ready);
        sem_wait(&sem_corto_plazo);
        sem_wait(&sem_mutex_colas);
        t_tcb *tcb_a_enviar = list_remove(QUEUE_READY, 0);
        list_add(QUEUE_EXEC, tcb_a_enviar);
        sem_post(&sem_mutex_colas);
        dispatcher(tcb_a_enviar->tid, tcb_a_enviar->ppid);
    }
}

void ejecutar_prioridades()
{
    while (1)
    {

        sem_wait(&sem_contador_ready);
        sem_wait(&sem_corto_plazo);
        sem_wait(&sem_mutex_colas);
        t_tcb *tcb_a_enviar = list_remove(QUEUE_READY, 0);
        list_add(QUEUE_EXEC, tcb_a_enviar);
        sem_post(&sem_mutex_colas);
        dispatcher(tcb_a_enviar->tid, tcb_a_enviar->ppid);
    }
}

void ejecutar_cmn()
{
    while (1)
    {
        sem_wait(&sem_contador_ready);
        sem_wait(&sem_corto_plazo);
        sem_wait(&sem_mutex_colas);

        t_tcb *tcb_a_enviar = list_remove(QUEUE_READY, 0);
        list_add(QUEUE_EXEC, tcb_a_enviar);
        sem_post(&sem_mutex_colas);
        dispatcher(tcb_a_enviar->tid, tcb_a_enviar->ppid);
        char *mensaje = string_new();
        string_append(&mensaje, "FIN_QUANTUM ");
        string_append(&mensaje, string_itoa(tcb_a_enviar->ppid));
        string_append(&mensaje, " ");
        string_append(&mensaje, string_itoa(tcb_a_enviar->tid));
        // Inicio hilo quantum
        pthread_t hilo_quantum;
        pthread_create(&hilo_quantum,
                       NULL,
                       aviso_quantum,
                       mensaje);
        pthread_detach(hilo_quantum);
    }
}

void dispatcher(int tid, int pid)
{

    char *tid_a_enviar = string_itoa(tid);
    char *pid_a_enviar = string_itoa(pid);

    char *mensaje = string_new();

    string_append(&mensaje, "PROXIMO_PROCESO ");
    string_append(&mensaje, pid_a_enviar);
    string_append(&mensaje, " ");
    string_append(&mensaje, tid_a_enviar);

    enviar_mensaje(mensaje, socket_cpu_dispatch);
}

int get_index(int prioridad)
{

    int index = 0;
    if (list_size(QUEUE_READY) > 0)
    {
        t_tcb *elemento = list_get(QUEUE_READY, 0);

        while (elemento->prioridad <= prioridad && index < list_size(QUEUE_READY))
        {

            elemento = list_get(QUEUE_READY, index);
            index++;
        }
    }
    return index;
}

char *recibir_desde_memoria(int socket_cliente)
{

    t_list *lista;
    int cod_op = recibir_operacion(socket_cliente);
    switch (cod_op)
    {
    case MENSAJE:
        int size;
        char *buffer = recibir_buffer(&size, socket_cliente);
        char *mensaje = string_duplicate(buffer);
        free(buffer);
        return mensaje;
        break;
    case PAQUETE:
        lista = recibir_paquete(socket_cliente);
        list_iterate(lista, (void *)iterator);
        break;
    case -1:
        log_error(logger, "El cliente se desconecto.");
        return EXIT_FAILURE;
    default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata");
        break;
    }
}

void aviso_quantum(char *mensaje)
{

    int quantum_milisecons = quantum * 1000;
    usleep(quantum_milisecons);
    enviar_mensaje(mensaje, socket_cpu_interrupt);
}

char *recibir_desde_cpu(int socket_cliente)
{

    t_list *lista;
    int cod_op = recibir_operacion(socket_cliente);
    switch (cod_op)
    {
    case MENSAJE: // validar que mensajes llegan desde CPU
        int size;
        char *buffer = recibir_buffer(&size, socket_cliente);
        char *mensaje = buffer;
        // void * mensaje;
        char **mensaje_split;
        mensaje_split = string_split(mensaje, " ");
        if (strcmp(mensaje_split[0], "INTERRUPCION_FIN_QUANTUM") == 0) // "INTERRUPCION_FIN_QUATUM",  "INTERRUPCION_FIN_HILO", "INTERRUPCION_I_O"
        {
            log_info(logger, "## (%s:%s) - Desalojado por fin de Quantum", mensaje_split[1], mensaje_split[2]);
            replanificar_hilo(atoi(mensaje_split[1]), atoi(mensaje_split[2]));
        }
        else if (strcmp(mensaje_split[0], "PROCESS_CREATE") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: PROCESS_CREATE", mensaje_split[1], mensaje_split[2]);
            sys_crear_proceso(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]), atoi(mensaje_split[5]));
        }
        else if (strcmp(mensaje_split[0], "PROCESS_EXIT") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: PROCESS_EXIT", mensaje_split[1], mensaje_split[2]);
            sys_process_exit(atoi(mensaje_split[1]), atoi(mensaje_split[2]));
        }
        else if (strcmp(mensaje_split[0], "THREAD_CREATE") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: THREAD_CREATE", mensaje_split[3], mensaje_split[4]);
            sys_thread_create(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]));
        }
        else if (strcmp(mensaje_split[0], "THREAD_JOIN") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: THREAD_JOIN", mensaje_split[2], mensaje_split[3]);
            sys_thread_join(atoi(mensaje_split[1]), atoi(mensaje_split[2]), atoi(mensaje_split[3]));
        }
        else if (strcmp(mensaje_split[0], "THREAD_CANCEL") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: THREAD_CANCEL", mensaje_split[1], mensaje_split[2]);
            sys_thread_cancel(atoi(mensaje_split[1]), atoi(mensaje_split[2]), atoi(mensaje_split[3]));
        }
        else if (strcmp(mensaje_split[0], "THREAD_EXIT") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: THREAD_EXIT", mensaje_split[1], mensaje_split[2]);
            sys_thread_exit(atoi(mensaje_split[1]), atoi(mensaje_split[2]));
        }
        else if (strcmp(mensaje_split[0], "MUTEX_CREATE") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: MUTEX_CREATE", mensaje_split[1], mensaje_split[2]);
            sys_mutex_create(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]));
        }
        else if (strcmp(mensaje_split[0], "MUTEX_LOCK") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: MUTEX_LOCK", mensaje_split[1], mensaje_split[2]);
            sys_mutex_lock(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]));
        }
        else if (strcmp(mensaje_split[0], "MUTEX_UNLOCK") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: MUTEX_UNLOCK", mensaje_split[1], mensaje_split[2]);
            sys_mutex_unlock(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]));
        }
        else if (strcmp(mensaje_split[0], "DUMP_MEMORY") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: DUMP_MEMORY", mensaje_split[1], mensaje_split[2]);
            sys_dump_memory(atoi(mensaje_split[1]), atoi(mensaje_split[2]));
        }
        else if (strcmp(mensaje_split[0], "IO") == 0)
        {
            log_info(logger, "## (%s:%s) - Solicitó syscall: IO", mensaje_split[1], mensaje_split[2]);
            sys_io(atoi(mensaje_split[1]), atoi(mensaje_split[2]), atoi(mensaje_split[3]));
        }

        free(buffer);
        return mensaje;
        break;
    case PAQUETE:
        lista = recibir_paquete(socket_cliente);
        list_iterate(lista, (void *)iterator);
        break;
    case -1:
        log_error(logger, "El cliente se desconecto.");
        return EXIT_FAILURE;
    default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata");
        break;
    }
}

void replanificar_hilo(int pid, int tid)
{

    bool _es_tcb_buscado(void *elemento)
    {
        return es_tcb_buscado(pid, tid, elemento);
    }
    t_tcb *tcb_encontrado;
    sem_wait(&sem_mutex_colas);
    tcb_encontrado = list_remove_by_condition(QUEUE_EXEC, _es_tcb_buscado);
    int index = get_index(tcb_encontrado->prioridad);
    list_add_in_index(QUEUE_READY, index, tcb_encontrado);
    sem_post(&sem_contador_ready);
    sem_post(&sem_mutex_colas);
}

void desbloquear_hilos_join(int tid_join, int ppid)
{
    int tamanio_lista_bloqueados = list_size(TCB_BLOQUEADOS);
    for (int i = 0; i < tamanio_lista_bloqueados; i++)
    {
        t_hilo_join *hilo_a_debloquear = list_get(TCB_BLOQUEADOS, i);
        if (hilo_a_debloquear->tid_join == tid_join && hilo_a_debloquear->ppid == ppid)
        {
            bool _es_tcb_buscado(void *elemento)
            {
                return es_tcb_buscado(hilo_a_debloquear->ppid, hilo_a_debloquear->tid, elemento);
            }
            t_tcb *tcb_encontrado;
            tcb_encontrado = list_remove_by_condition(QUEUE_BLOCKED, _es_tcb_buscado);
            if (strcmp(algoritmo_planificacion, "FIFO") == 0)
            {

                list_add(QUEUE_READY, tcb_encontrado);

            }
            else if (strcmp(algoritmo_planificacion, "PRIORIDADES") == 0 || strcmp(algoritmo_planificacion, 'CMN') == 0)
            {

                int index = get_index(tcb_encontrado->prioridad);
                list_add_in_index(QUEUE_READY, index, tcb_encontrado);
            }
            t_hilo_join *auxiliar_hilo = list_remove(TCB_BLOQUEADOS, i);
            free(auxiliar_hilo);
            sem_post(&sem_contador_ready);
        }
    }
}
void esperar_respuesta_dump_memory()
{

    t_list *lista;
    int cod_op = recibir_operacion(socket_memoria);
    switch (cod_op)
    {
    case MENSAJE:
        int size;
        char *buffer = recibir_buffer(&size, socket_memoria);
        char **mensaje_split = string_split(buffer, " ");

        if (strcmp(mensaje_split[0], "DUMP_MEMORY_SUCCESS") == 0)
        {
            int pid_recibido = atoi(mensaje_split[1]);
            int tid_recibido = atoi(mensaje_split[2]);
            bool _es_tcb_buscado(void *elemento)
            {
                return es_tcb_buscado(pid_recibido, tid_recibido, elemento);
            }
            sem_wait(&sem_mutex_colas);
            t_tcb *tcb_encontrado_blocked = list_find(QUEUE_BLOCKED, _es_tcb_buscado);
            list_remove_element(QUEUE_BLOCKED, tcb_encontrado_blocked);
            asignar_a_ready(tcb_encontrado_blocked);
            sem_post(&sem_mutex_colas);
        }
        else if (strcmp(mensaje_split[0], "DUMP_MEMORY_FAIL") == 0)
        {
            int pid_recibido = atoi(mensaje_split[1]);
            int tid_recibido = atoi(mensaje_split[2]);
            finalizar_hilo(pid_recibido, tid_recibido, QUEUE_BLOCKED);
        }
        free(buffer);
        break;
    case PAQUETE:
        lista = recibir_paquete(socket_memoria);
        list_iterate(lista, (void *)iterator);
        break;
    case -1:
        log_error(logger, "El cliente se desconecto.");
        return EXIT_FAILURE;
    default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata");
        break;
    }
}

void recibir_mensajes_cpu()
{
    while (1)
    {
        recibir_desde_cpu(socket_cpu_dispatch);
    }
}