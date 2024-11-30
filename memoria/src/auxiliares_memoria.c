#include <../include/auxiliares_memoria.h>

void iniciar_memoria_fija(char **particiones_array)
{
  int posicion = 0;
  int i = 0;
  while (particiones_array[i] != NULL)
  {
    t_particion *particion = malloc(sizeof(t_particion));
    particion->pid = -1;
    particion->BASE = posicion;
    posicion += atoi(particiones_array[i]);
    particion->LIMITE = particiones_array[i];
    list_add(lista_particiones, particion);
    i++;
  }
}

void iniciar_memoria_dinamica()
{
  t_particion *particion = malloc(sizeof(t_particion));
  particion->pid = -1;
  particion->BASE = 0;
  particion->LIMITE = tamanio_memoria;
  list_add(lista_particiones, particion);
}

bool hay_espacio(int tamanio_necesario)
{
  bool respuesta = false;
  int i = 0;
  t_particion *particion;
  while (i < list_size(lista_particiones) && respuesta == false)
  {
    particion = list_get(lista_particiones, i);
    if (particion->pid == -1 && tamanio_necesario <= particion->LIMITE)
    {
      respuesta = true;
    }
    i++;
  }

  return respuesta;
}

void crear_proceso(char *archivo_instrucciones, int tamanio, int prioridad, int pid, int socket_cliente)
{

  // Se valida que haya espacio
  char *mensaje_resultado = string_new();
  if (!hay_espacio(tamanio))
  {
    string_append(&mensaje_resultado, "PROCESS_CREATE_FAIL ");
    string_append(&mensaje_resultado, string_itoa(pid));
    enviar_mensaje(mensaje_resultado, socket_cliente);
    return;
  }

  // Se obtiene la particion asignada
  t_particion *particion_asignada = asignar_particion(tamanio, pid);

  t_contexto_proceso *proceso = malloc(sizeof(t_contexto_proceso));

  proceso->pid = pid;
  proceso->BASE = particion_asignada->BASE;
  proceso->LIMITE = tamanio;

  list_add(procesos, proceso);
  crear_hilo(archivo_instrucciones, prioridad, pid, 0, socket_cliente);
  usleep(retardo_respuesta_cpu * 1000);

  string_append(&mensaje_resultado, "PROCESS_CREATE_OK ");
  string_append(&mensaje_resultado, string_itoa(pid));
  enviar_mensaje(mensaje_resultado, socket_cliente);
  log_info(logger,"## Proceso Creado - PID: - (%d:) - Tamaño: %d", pid, tamanio);
}

t_particion *asignar_particion(int tamanio, int pid)
{
  t_particion *particion_asignada;

  if (strcmp(algoritmo, "FIRST") == 0)
  {
    particion_asignada = first_fit(tamanio, pid);
  }
  else if (strcmp(algoritmo, "BEST") == 0)
  {
    particion_asignada = best_fit(tamanio, pid);
  }

  else if (strcmp(algoritmo, "WORST") == 0)
  {
    particion_asignada = worst_fit(tamanio, pid);
  }

  return particion_asignada;
}

t_particion *first_fit(int tamanio_necesario, int pid)
{

  t_particion *particion;

  int i = 0;
  for (i; i < list_size(lista_particiones); i++)
  {

    particion = list_get(lista_particiones, i);
    if (particion->pid == -1 && tamanio_necesario <= particion->LIMITE)
    {
      break;
    }
  }

  if (strcmp(esquema, "DINAMICAS") == 0)
  {
    if (particion->LIMITE > tamanio_necesario)
    {

      t_particion *particion_siguiente = malloc(sizeof(t_particion));
      particion_siguiente->pid = -1;
      particion_siguiente->BASE = particion->BASE + tamanio_necesario;
      particion_siguiente->LIMITE = particion->LIMITE - tamanio_necesario;

      particion->LIMITE = tamanio_necesario;
      list_add_in_index(lista_particiones, i + 1, particion_siguiente);
    }
  }

  particion->pid = pid;
  return particion;
}

t_particion *best_fit(int tamanio_necesario, int pid)
{
  t_particion *particion_aux;
  t_particion *particion_best;
  int i = 0;
  for (i; i < list_size(lista_particiones); i++)
  {

    particion_aux = list_get(lista_particiones, i);
    if (particion_aux->pid == -1 && tamanio_necesario <= particion_aux->LIMITE)
    {
      particion_best = particion_aux;
      break;
    }
  }

  i++;
  for (i; i < list_size(lista_particiones); i++)
  {
    particion_aux = list_get(lista_particiones, i);
    if (particion_aux->pid == -1 && tamanio_necesario <= particion_aux->LIMITE && particion_aux->LIMITE < particion_best->LIMITE)
    {
      particion_best = particion_aux;
    }
  }

  if (strcmp(esquema, "DINAMICAS") == 0)
  {
    if (particion_best->LIMITE > tamanio_necesario)
    {

      t_particion *particion_siguiente = malloc(sizeof(t_particion));
      particion_siguiente->pid = -1;
      particion_siguiente->BASE = particion_best->BASE + tamanio_necesario;
      particion_siguiente->LIMITE = particion_best->LIMITE - tamanio_necesario;

      particion_best->LIMITE = tamanio_necesario;
      list_add_in_index(lista_particiones, i + 1, particion_siguiente);
    }
  }

  particion_best->pid = pid;
  return particion_best;
}

t_particion *worst_fit(int tamanio_necesario, int pid)
{
  t_particion *particion_aux;
  t_particion *particion_worst;
  int i = 0;
  for (i; i < list_size(lista_particiones); i++)
  {

    particion_aux = list_get(lista_particiones, i);
    if (particion_aux->pid == -1 && tamanio_necesario <= particion_aux->LIMITE)
    {
      particion_worst = particion_aux;
      break;
    }
  }

  i++;
  for (i; i < list_size(lista_particiones); i++)
  {
    particion_aux = list_get(lista_particiones, i);
    if (particion_aux->pid == -1 && tamanio_necesario <= particion_aux->LIMITE && particion_aux->LIMITE > particion_worst->LIMITE)
    {
      particion_worst = particion_aux;
    }
  }

  if (strcmp(esquema, "DINAMICAS") == 0)
  {
    if (particion_worst->LIMITE > tamanio_necesario)
    {

      t_particion *particion_siguiente = malloc(sizeof(t_particion));
      particion_siguiente->pid = -1;
      particion_siguiente->BASE = particion_worst->BASE + tamanio_necesario;
      particion_siguiente->LIMITE = particion_worst->LIMITE - tamanio_necesario;

      particion_worst->LIMITE = tamanio_necesario;
      list_add_in_index(lista_particiones, i + 1, particion_siguiente);
    }
  }

  particion_worst->pid = pid;
  return particion_worst;
}

void crear_hilo(char *archivo_instrucciones, int prioridad, int pid, int tid, int socket_cliente)
{
  t_contexto_hilo *hilo = malloc(sizeof(t_contexto_hilo));
  hilo->pid = pid;
  hilo->tid = tid;
  hilo->contexto_hilo = malloc(sizeof(t_contexto));
  hilo->instrucciones = list_create();
  hilo->contexto_hilo->PC = 0;
  hilo->contexto_hilo->AX = 0;
  hilo->contexto_hilo->BX = 0;
  hilo->contexto_hilo->CX = 0;
  hilo->contexto_hilo->DX = 0;
  hilo->contexto_hilo->EX = 0;
  hilo->contexto_hilo->FX = 0;
  hilo->contexto_hilo->GX = 0;
  hilo->contexto_hilo->HX = 0;
  leer_instrucciones(archivo_instrucciones, hilo->instrucciones);
  list_add(hilos, hilo);
  log_info(logger,"## Hilo Creado - (PID:TID) - (%d:%d)", pid, tid);
}

void leer_instrucciones(char *path, t_list *lista_instrucciones)
{
  char *archivo_instrucciones = string_new();
  string_append(&archivo_instrucciones, path_instrucciones);
  string_append(&archivo_instrucciones, "/");
  string_append(&archivo_instrucciones, path);
  FILE *f = fopen(archivo_instrucciones, "r");
  fseek(f, 0L, SEEK_END);
  int size_file = ftell(f);
  rewind(f);
  char *texto_completo = malloc(size_file + 1);
  size_t bytes_leidos = fread(texto_completo, sizeof(char), size_file, f);
  texto_completo[bytes_leidos] = '\0';
  char **instrucciones_split = string_array_new();
  instrucciones_split = string_split(texto_completo, "\n");

  int i = 0;
  int length = string_array_size(instrucciones_split);
  while (i < length)
  {
    list_add(lista_instrucciones, instrucciones_split[i]);
    i++;
  }

  fclose(f);
}

pthread_t iniciar_hilo_server_memoria(char *puerto)
{
  int socket_servidor = iniciar_servidor(puerto);

  pthread_t hiloAtencion;
  pthread_create(&hiloAtencion,
                 NULL,
                 (void *)hilo_cliente_memoria,
                 socket_servidor);

  return hiloAtencion;
}

void hilo_cliente_memoria(int socket_servidor)
{
  while (1)
  {

    int socket_cliente = esperar_cliente(socket_servidor);
    pthread_t hiloCliente;
    pthread_create(&hiloCliente,
                   NULL,
                   (void *)atender_cliente_memoria,
                   socket_cliente);
    pthread_detach(hiloCliente);
  }
}

void atender_cliente_memoria(int socket_cliente)
{
  int cod_op;
  int size;
  char *buffer;
  t_list *lista;

  while (1)
  {
    t_atencion_mensaje *param_atencion_mensaje = malloc(sizeof(t_atencion_mensaje));
    t_atencion_paquete *param_atencion_paquete = malloc(sizeof(t_atencion_paquete));
    cod_op = recibir_operacion(socket_cliente);
    switch (cod_op)
    {
    case MENSAJE:
      buffer = recibir_buffer(&size, socket_cliente);

      param_atencion_mensaje->buffer = string_duplicate(buffer);
      free(buffer);
      param_atencion_mensaje->socket_cliente = socket_cliente;
      pthread_t hiloAtencionMensaje;
      pthread_create(&hiloAtencionMensaje,
                     NULL,
                     (void *)entender_mensaje_memoria,
                     param_atencion_mensaje);
      pthread_detach(hiloAtencionMensaje);

      break;
    case PAQUETE:

      lista = recibir_paquete(socket_cliente);

      param_atencion_paquete->lista = list_duplicate(lista);
      param_atencion_paquete->socket_cliente = socket_cliente;
      pthread_t hiloAtencionPaquete;
      pthread_create(&hiloAtencionPaquete,
                     NULL,
                     (void *)entender_paquete_memoria,
                     param_atencion_paquete);
      pthread_detach(hiloAtencionPaquete);
      break;
    case -1:
      log_error(logger, "El cliente se desconecto.");
      return EXIT_FAILURE;
    default:
      log_warning(logger, "Operacion desconocida. No quieras meter la pata.");
      break;
    }
  }
}

void entender_mensaje_memoria(t_atencion_mensaje *param_atencion)
{
  char *buffer = param_atencion->buffer;
  int socket_cliente = param_atencion->socket_cliente;

  char **mensaje_split = string_split(buffer, " ");

  if (string_starts_with(buffer, "PROXIMA_INSTRUCCION"))
  {
    proxima_instruccion(atoi(mensaje_split[1]), atoi(mensaje_split[2]), atoi(mensaje_split[3]), socket_cliente);
  }
  else if (string_starts_with(buffer, "OBTENER_CONTEXTO"))
  {
    obtener_contexto(atoi(mensaje_split[1]), atoi(mensaje_split[2]), socket_cliente);
  }
   else if (string_starts_with(buffer, "FINALIZAR_HILO"))
  {
    finalizar_hilo(atoi(mensaje_split[1]), atoi(mensaje_split[2]), socket_cliente);
  }
  else if (string_starts_with(buffer, "PROCESS_CREATE"))
  {
    crear_proceso(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]), socket_cliente);
  }
  else if (string_starts_with(buffer, "PROCESS_EXIT"))
  {
    finalizar_proceso(atoi(mensaje_split[1]), socket_cliente);
  }
  else if (string_starts_with(buffer, "THREAD_CREATE"))
  {
    crear_hilo(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]), socket_cliente);
  }
  else if (string_starts_with(buffer, "READ_MEM"))
  {
    read_mem(atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]), socket_cliente);
  }
  else if (string_starts_with(buffer, "CONEXION_INICIAL_KERNEL"))
  {
    conexion_inicial_kernel(socket_cliente);
  }
  else if (string_starts_with(buffer, "DUMP_MEMORY"))
  {
    dump_memory(atoi(mensaje_split[1]), atoi(mensaje_split[2]), socket_cliente);
  }

  free(buffer);
}

void dump_memory(int pid, int tid, int socket_cliente)
{
  char *timestamp = temporal_get_string_time("%H:%M:%S:%MS");
  char *nombre_archivo = string_new();
  string_append(&nombre_archivo, string_itoa(pid));
  string_append(&nombre_archivo, "-");
  string_append(&nombre_archivo, string_itoa(tid));
  string_append(&nombre_archivo, "-");
  string_append(&nombre_archivo, timestamp);
  free(timestamp);
  t_contexto_proceso *contexto_proceso = find_by_pid(procesos, pid);
  t_paquete *paquete = crear_paquete();
  agregar_a_paquete(paquete, "DUMP_MEMORY", 12);
  agregar_a_paquete(paquete, nombre_archivo, string_length(nombre_archivo) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto_proceso->LIMITE), string_length(string_itoa(contexto_proceso->LIMITE)) + 1);
  agregar_a_paquete(paquete, memoria_principal + (contexto_proceso->BASE), contexto_proceso->LIMITE);
  enviar_paquete(paquete, socket_filesystem);
  log_info(logger, "## Memory Dump solicitado - (PID:TID) - (%d:%d)", pid, tid);

  int cod_op = recibir_operacion(socket_filesystem);
  int size;
  switch (cod_op)
  {
  case MENSAJE:
    char *buffer = recibir_buffer(&size, socket_filesystem);
    enviar_mensaje(buffer, socket_cliente);
    break;
  case PAQUETE:
    break;
  case -1:
    log_error(logger, "El cliente se desconecto.");
    return EXIT_FAILURE;
  default:
    log_warning(logger, "Operacion desconocida. No quieras meter la pata.");
    break;
  }
}

void conexion_inicial_kernel(int socket_cliente)
{
  socket_kernel = socket_cliente;
  log_info(logger, "## Kernel Conectado - FD del socket: %d", socket_kernel);
}

void read_mem(int direccion_fisica, int pid, int tid, int socket_cliente)
{
  t_paquete *respuesta = crear_paquete();
  char *operacion = string_new();
  string_append(&operacion, "READ_MEM");
  agregar_a_paquete(respuesta, operacion, string_length(operacion) + 1);
  void *dato = malloc(4);
  memcpy(dato, memoria_principal + direccion_fisica, 4);
  agregar_a_paquete(respuesta, dato, 4);
  usleep(retardo_respuesta_cpu * 1000);
  log_info(logger, "## Lectura - (PID:TID) - (%d:%d) - Dir. Física: %d - Tamaño: 4", pid, tid, direccion_fisica);
  enviar_paquete(respuesta, socket_cliente);
}

void write_mem(int direccion_fisica, void *datos, int pid, int tid, int socket_cliente)
{
  memcpy(memoria_principal + direccion_fisica, datos, 4);
  usleep(retardo_respuesta_cpu * 1000);
  char *respuesta = string_new();
  usleep(retardo_respuesta_cpu * 1000);
  log_info(logger, "## Escritura - (PID:TID) - (%d:%d) - Dir. Física: %d - Tamaño: 4", pid, tid, direccion_fisica);
  string_append(&respuesta, "WRITE_MEM OK");
  enviar_mensaje(respuesta, socket_cliente);
}

void proxima_instruccion(int pid, int tid, int pc, int socket_cliente)
{
  char *instruccion = string_new();
  string_append(&instruccion, "PROXIMA_INSTRUCCION ");
  t_contexto_hilo *contexto = find_by_pid_tid(hilos, pid, tid);

  if (contexto != NULL)
  {
    string_append(&instruccion, list_get(contexto->instrucciones, pc));
  }
  else
  {
    string_append(&instruccion, "No exite dicho PID-TID");
  }

  usleep(retardo_respuesta_cpu * 1000);
  log_info(logger, "## Obtener instrucción - (PID:TID) - (%d:%d) - Instrucción: %s", pid, tid, list_get(contexto->instrucciones, pc));
  enviar_mensaje(instruccion, socket_cliente);
}

t_contexto_hilo *find_by_pid_tid(t_list *hilos, int pid, int tid)
{
  bool _pid_tid(void *ptr)
  {
    t_contexto_hilo *contexto = (t_contexto_hilo *)ptr;
    if (contexto->pid == pid && contexto->tid == tid)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return list_find(hilos, _pid_tid);
}

void obtener_contexto(int pid, int tid, int socket_cliente)
{
  t_contexto_hilo *contexto = find_by_pid_tid(hilos, pid, tid);
  if (contexto == NULL)
  {
    enviar_mensaje("NO EXISTE PID-TID", socket_cliente);
    return;
  }

  t_contexto_proceso *contexto_proceso = find_by_pid(procesos, pid);

  char *mensaje = string_new();
  string_append(&mensaje, "OBTENER_CONTEXTO");

  t_paquete *paquete = crear_paquete();
  agregar_a_paquete(paquete, mensaje, string_length(mensaje) + 1);
  agregar_a_paquete(paquete, string_itoa(pid), string_length(string_itoa(pid)) + 1);
  agregar_a_paquete(paquete, string_itoa(tid), string_length(string_itoa(tid)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->PC), string_length(string_itoa(contexto->contexto_hilo->PC)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->AX), string_length(string_itoa(contexto->contexto_hilo->AX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->BX), string_length(string_itoa(contexto->contexto_hilo->BX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->CX), string_length(string_itoa(contexto->contexto_hilo->CX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->DX), string_length(string_itoa(contexto->contexto_hilo->DX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->EX), string_length(string_itoa(contexto->contexto_hilo->EX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->FX), string_length(string_itoa(contexto->contexto_hilo->FX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->GX), string_length(string_itoa(contexto->contexto_hilo->GX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto->contexto_hilo->HX), string_length(string_itoa(contexto->contexto_hilo->HX)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto_proceso->BASE), string_length(string_itoa(contexto_proceso->BASE)) + 1);
  agregar_a_paquete(paquete, string_itoa(contexto_proceso->LIMITE), string_length(string_itoa(contexto_proceso->LIMITE)) + 1);

  usleep(retardo_respuesta_cpu * 1000);
  log_info(logger, "## Contexto Solicitado - (PID:TID) - (%d:%d)", pid, tid);

  enviar_paquete(paquete, socket_cliente);
}

void actualizar_contexto(t_list *lista, int socket_cliente)
{
  t_contexto_hilo *contexto = find_by_pid_tid(hilos, atoi(list_get(lista, 1)), atoi(list_get(lista, 2)));
  contexto->contexto_hilo->PC = atoi(list_get(lista, 3));
  contexto->contexto_hilo->AX = atoi(list_get(lista, 4));
  contexto->contexto_hilo->BX = atoi(list_get(lista, 5));
  contexto->contexto_hilo->CX = atoi(list_get(lista, 6));
  contexto->contexto_hilo->DX = atoi(list_get(lista, 7));
  contexto->contexto_hilo->EX = atoi(list_get(lista, 8));
  contexto->contexto_hilo->FX = atoi(list_get(lista, 9));
  contexto->contexto_hilo->GX = atoi(list_get(lista, 10));
  contexto->contexto_hilo->HX = atoi(list_get(lista, 11));
  usleep(retardo_respuesta_cpu * 1000);
  log_info(logger, "## Contexto Actualizado - (PID:TID) - (%s:%s)", list_get(lista, 1), list_get(lista, 2));

  enviar_mensaje("CONTEXTO_GUARDADO", socket_cliente);
}

void entender_paquete_memoria(t_atencion_paquete *param_atencion)
{
  t_list *lista = param_atencion->lista;
  int socket_cliente = param_atencion->socket_cliente;

  if (string_starts_with(list_get(lista, 0), "ACTUALIZAR_CONTEXTO"))
  {
    actualizar_contexto(lista, socket_cliente);
  }
  else if (string_starts_with(list_get(lista, 0), "WRITE_MEM"))
  {
    write_mem(atoi(list_get(lista, 1)), list_get(lista, 2), atoi(list_get(lista, 3)), atoi(list_get(lista, 4)), socket_cliente);
  }
}

t_contexto_hilo *find_by_pid(t_list *procesos, int pid)
{
  bool _pid(void *ptr)
  {
    t_contexto_proceso *contexto = (t_contexto_proceso *)ptr;
    if (contexto->pid == pid)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return list_find(procesos, _pid);
}

void consolidar(int posicion)
{
  if (strcmp(esquema, "DINAMICAS") == 0 && list_size(lista_particiones) > 1)
  {

    if (posicion == 0)
    {
      t_particion *particion_posterior = list_get(lista_particiones, posicion + 1);
      t_particion *particion = list_get(lista_particiones, posicion);
      if (particion_posterior->pid == -1)
      {
        particion->LIMITE = particion->LIMITE + particion_posterior->LIMITE;
        list_remove(lista_particiones, posicion + 1);
      }
    }
    else if (posicion > 0 && posicion < list_size(lista_particiones) - 1)
    {

      t_particion *particion_anterior = list_get(lista_particiones, posicion - 1);
      t_particion *particion = list_get(lista_particiones, posicion);
      t_particion *particion_posterior = list_get(lista_particiones, posicion + 1);
      if (particion_anterior->pid == -1 && particion_posterior->pid == -1)
      {
        particion_anterior->LIMITE = particion_anterior->LIMITE + particion_posterior->LIMITE + particion->LIMITE;
        list_remove(lista_particiones, posicion + 1);
        list_remove(lista_particiones, posicion);
      }
      else if (particion_anterior->pid != -1 && particion_posterior->pid == -1)
      {
        particion->LIMITE = particion_posterior->LIMITE + particion->LIMITE;
        list_remove(lista_particiones, posicion + 1);
      }
      else if (particion_anterior->pid == -1 && particion_posterior->pid != -1)
      {
        particion_anterior->LIMITE = particion_anterior->LIMITE + particion->LIMITE;
        list_remove(lista_particiones, posicion);
      }
    }
    else if (posicion == list_size(lista_particiones) - 1)
    {
      t_particion *particion_anterior = list_get(lista_particiones, posicion - 1);
      t_particion *particion = list_get(lista_particiones, posicion);
      if (particion_anterior->pid == -1)
      {
        particion_anterior->LIMITE = particion_anterior->LIMITE + particion->LIMITE;
        list_remove(lista_particiones, posicion);
      }
    }
  }
}

void finalizar_hilo(int pid, int tid, int socket_cliente)
{

  t_contexto_hilo *hilo_a_eliminar = find_by_pid_tid(hilos, pid, tid);
  if (hilo_a_eliminar != NULL)
  {
    free(hilo_a_eliminar->contexto_hilo);
    list_destroy(hilo_a_eliminar->instrucciones);
    list_remove_element(hilos, hilo_a_eliminar);
    free(hilo_a_eliminar);
    log_info(logger,"## Hilo Destruido - (PID:TID) - (%d:%d)", pid, tid);
  }
  enviar_mensaje("OK", socket_cliente);
}

void finalizar_proceso(int pid, int socket_cliente)
{
  t_particion *particion = particion_buscada(pid);
  if (particion != NULL)
  {
    particion->pid = -1;

    int index = obtener_posicion_particion(pid);
    t_contexto_proceso *contexto_proceso = find_by_pid(procesos, pid);
    list_remove_element(procesos, contexto_proceso);
    log_info(logger, "## Proceso Destruido -  PID: %d - Tamaño: %d", pid, contexto_proceso->LIMITE);
    free(contexto_proceso);
    if (esquema == "DINAMICAS" && index != -1)
    {
      consolidar(index);
    }
  }
}

t_particion *particion_buscada(int pid)
{

  bool _pid(void *ptr)
  {
    t_particion *particion = (t_particion *)ptr;
    if (particion->pid == pid)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return list_find(lista_particiones, _pid);
}

int obtener_posicion_particion(int pid)
{
  int index = -1;
  t_particion *particion;
  for (int i = 0; list_size(lista_particiones) > i; i++)
  {
    particion = list_get(lista_particiones, i);
    if (particion->pid == pid)
    {
      index = i;
    }
  }
  return index;
}