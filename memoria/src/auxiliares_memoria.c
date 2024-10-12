#include <../include/auxiliares_memoria.h>

void crear_proceso(char *archivo_instrucciones, int tamanio, int prioridad, int pid)
{

  /* /TODO se valida que haya espacio
  if (!hay_espacio())
  {
    //responder a kernel que no hay espacio
    return;
  }

  //se valida el esquema
  if (esquema == "FIJAS") {
    return;

  }else if (esquema == "DINAMICAS")
  {

  return;
  }
*/
  t_contexto_proceso *proceso = malloc(sizeof(t_contexto_proceso));

  proceso->pid = pid;
  proceso->BASE = 0; // TODO calcular base
  proceso->LIMITE = proceso->BASE + tamanio;

  list_add(procesos, proceso);
  crear_hilo(archivo_instrucciones, prioridad, pid, 0);
  usleep(retardo_respuesta_cpu * 1000);
}

void crear_hilo(char *archivo_instrucciones, int prioridad, int pid, int tid)
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
    crear_proceso(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]));
  }
  else if (string_starts_with(buffer, "THREAD_CREATE"))
  {
    crear_hilo(mensaje_split[1], atoi(mensaje_split[2]), atoi(mensaje_split[3]), atoi(mensaje_split[4]));
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
  t_contexto_hilo *contexto = find_by_pid_tid(hilos, lista[1], lista[2]);
  if (contexto == NULL)
  {
    enviar_mensaje("NO EXISTE PID-TID", socket_cliente);
    return;
  }
  t_paquete *paquete = crear_paquete();
  agregar_a_paquete(paquete, pid, sizeof(int));
  agregar_a_paquete(paquete, tid, sizeof(int));
  agregar_a_paquete(paquete, contexto->PC, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->AX, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->BX, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->CX, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->DX, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->EX, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->FX, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->GX, sizeof(uint32_t));
  agregar_a_paquete(paquete, contexto->HX, sizeof(uint32_t));

  usleep(retardo_respuesta_cpu * 1000);
  enviar_paquete(paquete, socket_cliente);
}

void actualizar_contexto(t_list *lista, int socket_cliente)
{
  t_contexto_hilo *contexto = find_by_pid_tid(hilos, lista[1], lista[2]);

  contexto->PC = lista[3];
  contexto->AX = lista[4];
  contexto->BX = lista[5];
  contexto->CX = lista[6];
  contexto->DX = lista[7];
  contexto->EX = lista[8];
  contexto->FX = lista[9];
  contexto->GX = lista[10];
  contexto->HX = lista[11];

  usleep(retardo_respuesta_cpu * 1000);
  enviar_mensaje("OK", socket_cliente);
}

void entender_paquete_memoria(t_list *lista, int socket_cliente)
{
  if (string_starts_with(lista[0], "ACTUALIZAR_CONTEXTO"))
  {
    actualizar_contexto(lista, socket_cliente);
  }
}