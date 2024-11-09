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
    particion->LIMITE = posicion - 1;
    list_add(lista_particiones, particion);
    i++;
  }
}

void iniciar_memoria_dinamica()
{
  t_particion *particion = malloc(sizeof(t_particion));
  particion->pid = -1;
  particion->BASE = 0;
  particion->LIMITE = tamanio_memoria - 1;
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
    if (particion->pid == -1 && tamanio_necesario <= (particion->LIMITE - particion->BASE + 1))
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
  if (!hay_espacio(tamanio))
  {
    enviar_mensaje("PROCESS_CREATE MEMORIA_INSUFICIENTE", socket_cliente);
    return;
  }

  // Se obtiene la particion asignada
  t_particion *particion_asignada = asignar_particion(tamanio);

  t_contexto_proceso *proceso = malloc(sizeof(t_contexto_proceso));

  proceso->pid = pid;
  proceso->BASE = particion_asignada->BASE;
  proceso->LIMITE = particion_asignada->BASE + tamanio;

  list_add(procesos, proceso);
  crear_hilo(archivo_instrucciones, prioridad, pid, 0, socket_cliente);
  usleep(retardo_respuesta_cpu * 1000);

  enviar_mensaje("PROCESS_CREATE OK", socket_cliente);
}

t_particion *asignar_particion(tamanio)
{
  t_particion *particion_asignada;

  if (strcmp(esquema, "FIJAS") == 0)
  {
    if (strcmp(algoritmo, "FIRST") == 0)
    {
    }
    else if (strcmp(algoritmo, "BEST") == 0)
    {
    }

    else if (strcmp(algoritmo, "WORST") == 0)
    {
    }
  }
  else if (strcmp(esquema, "DINAMICAS") == 0)
  {
    if (strcmp(algoritmo, "FIRST") == 0)
    {
    }
    else if (strcmp(algoritmo, "BEST") == 0)
    {
    }

    else if (strcmp(algoritmo, "WORST") == 0)
    {
    }
  }
  return particion_asignada;
}

t_particion *first_fit()
{
  int i = 0;
  t_particion *particion;
  while (i < list_size(lista_particiones) && respuesta == false)
  {
    particion = list_get(lista_particiones, i);
    if (particion->pid == -1 && tamanio_necesario <= (particion->LIMITE - particion->BASE + 1))
    {
      respuesta = true;
    }
    i++;
  }
}

t_particion *best_fit()
{
}

t_particion *worst_fit()
{
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
}

void leer_instrucciones(char *path, t_list *lista_instrucciones)
{
  char *path_instrucciones = config_get_string_value(config, "PATH_INSTRUCCIONES");
  string_append(&path_instrucciones, "/");
  string_append(&path_instrucciones, path);
  FILE *f = fopen(path_instrucciones, "r");
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

  t_list *lista;
  while (1)
  {
    int cod_op = recibir_operacion(socket_cliente);

    switch (cod_op)
    {
    case MENSAJE:
      entender_mensaje_memoria(socket_cliente);
      break;
    case PAQUETE:
      lista = recibir_paquete(socket_cliente);
      entender_paquete_memoria(lista, socket_cliente);
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

void entender_mensaje_memoria(int socket_cliente)
{
  int size;
  char *buffer = recibir_buffer(&size, socket_cliente);
  char **mensaje_split = string_split(buffer, " ");

  if (string_starts_with(buffer, "PROXIMA_INSTRUCCION"))
  {
    proxima_instruccion(atoi(mensaje_split[1]), atoi(mensaje_split[2]), atoi(mensaje_split[3]), socket_cliente);
  }
  else if (string_starts_with(buffer, "OBTENER_CONTEXTO"))
  {
    obtener_contexto(atoi(mensaje_split[1]), atoi(mensaje_split[2]), socket_cliente);
  }
  else if (string_starts_with(buffer, "PROCESS_CREATE"))
  {
    crear_proceso(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]), socket_cliente);
  }
  else if (string_starts_with(buffer, "THREAD_CREATE"))
  {
    crear_hilo(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]), socket_cliente);
  }

  free(buffer);
}

void proxima_instruccion(int pid, int tid, int pc, int socket_cliente)
{
  char *instruccion;
  t_contexto_hilo *contexto = find_by_pid_tid(hilos, pid, tid);

  if (contexto != NULL)
  {
    instruccion = list_get(contexto->instrucciones, pc);
  }
  else
  {
    instruccion = "No exite dicho PID-TID";
  }

  usleep(retardo_respuesta_cpu * 1000);
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
  enviar_paquete(paquete, socket_cliente);
}

void actualizar_contexto(t_list *lista, int socket_cliente)
{
  t_contexto_hilo *contexto = find_by_pid_tid(hilos, list_get(lista, 1), list_get(lista, 2));
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
  enviar_mensaje("CONTEXTO_GUARDADO", socket_cliente);
}

void entender_paquete_memoria(t_list *lista, int socket_cliente)
{
  if (string_starts_with(list_get(lista, 0), "ACTUALIZAR_CONTEXTO"))
  {
    actualizar_contexto(lista, socket_cliente);
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