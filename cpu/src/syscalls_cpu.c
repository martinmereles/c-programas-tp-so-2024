#include <../include/syscalls_cpu.h>

/*----------------------------------SET DE "SYSCALLS"---------------------------------*/

void process_create(char * arch_instrucciones, char *tamanio, char *prioridad_tid){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();
    
    //enviar mensaje a Kernel PROCESS_CREATE arch_instrucciones tamanio prioridad_tid pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"PROCESS_CREATE ");
    string_append(&mensaje, arch_instrucciones);
    string_append(&mensaje, " ");
    string_append(&mensaje, tamanio);
    string_append(&mensaje, " ");
    string_append(&mensaje, prioridad_tid);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    
    log_info(logger, "## TID: %d - Ejecutando: PROCESS_CREATE - %s %s %s", tid, arch_instrucciones, tamanio, prioridad_tid);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void process_exit(){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();

    //enviar mensaje a Kernel PROCESS_EXIT pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"PROCESS_EXIT ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: PROCESS_EXIT", tid);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void thread_create(char * arch_instrucciones, char* prioridad){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();
    
    //enviar mensaje a Kernel THREAD_CREATE arch_instrucciones prioridad pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"THREAD_CREATE ");
    string_append(&mensaje, arch_instrucciones);
    string_append(&mensaje, " ");
    string_append(&mensaje, prioridad);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: THREAD_CREATE - %s %s ", tid, arch_instrucciones, prioridad);
    
    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void thread_join(char* tid_var){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();
    
    //enviar mensaje a Kernel THREAD_JOIN  tid_var pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"THREAD_JOIN ");
    string_append(&mensaje, tid_var);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: THREAD_EXIT - %s", tid, tid_var);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void thread_cancel(char* tid_var){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();

    //enviar mensaje a Kernel THREAD_CANCEL tid_var pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"THREAD_CANCEL ");
    string_append(&mensaje, tid_var);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: THREAD_CANCEL - %s", tid, tid_var);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void thread_exit(){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();
    
    //enviar mensaje a Kernel THREAD_EXIT pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"THREAD_EXIT ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: THREAD_EXIT", tid);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void mutex_create(char* recurso){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();

    //enviar mensaje a Kernel MUTEX_CREATE recurso pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"MUTEX_CREATE ");
    string_append(&mensaje, recurso);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: MUTEX_CREATE - %s", tid, recurso);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void mutex_lock(char* recurso){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();

    //enviar mensaje a Kernel MUTEX_LOCK recurso pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"MUTEX_LOCK ");
    string_append(&mensaje, recurso);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: MUTEX_LOCK - %s", tid, recurso);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void mutex_unlock(char* recurso){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();
    
    //enviar mensaje a Kernel MUTEX_UNLOCK recurso pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"MUTEX_UNLOCK ");
    string_append(&mensaje, recurso);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: MUTEX_LOCK - %s", tid, recurso);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void dump_memory(){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();

    //enviar mensaje a Kernel DUMP_MEMORY pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"DUMP_MEMORY ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: DUMP_MEMORY", tid);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}

void io(char* tiempo){

    //Crear paquete y enviar a memoria
    crear_paquete_contexto();
    
    //enviar mensaje a Kernel IO tiempo pid_contexto tid_contexto
    char* mensaje = string_new();
    string_append(&mensaje,"IO ");
    string_append(&mensaje, tiempo);
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(pid));
    string_append(&mensaje, " ");
    string_append(&mensaje, string_itoa(tid));
    enviar_mensaje(mensaje ,socket_kernel_dispatch);
    log_info(logger, "## TID: %d - Ejecutando: IO - %s", tid, tiempo);

    //para cortar validar si se debe cortar la ejecucion
    se_ejecuto_syscall = true;
}