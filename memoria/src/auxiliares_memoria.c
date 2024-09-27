#include <../include/auxiliares_memoria.h>


void crear_proceso (int pid, int tid,  char* archivo_instrucciones){
  
  /* /se valida que haya espacio
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
  t_contexto_proceso* proceso = malloc (sizeof(t_contexto_proceso));

  proceso->pid = pid;
  proceso->BASE = 0;
  proceso->LIMITE = 256;

  list_add (procesos, proceso);
crear_hilo(archivo_instrucciones, 0, pid, 0);

    
}

crear_hilo(char* archivo_instrucciones, int prioridad, int pid, int tid){

t_contexto_hilo* hilo = malloc(sizeof(t_contexto_hilo));
hilo->pid = pid;
hilo->tid = tid;
hilo->contexto_hilo = malloc(sizeof(t_contexto));
hilo->instrucciones = list_create();

hilo->contexto_hilo->AX = 0;
hilo->contexto_hilo->BX = 0;
hilo->contexto_hilo->CX = 0;
hilo->contexto_hilo->DX = 0;
hilo->contexto_hilo->EX = 0;
hilo->contexto_hilo->FX = 0;
hilo->contexto_hilo->GX = 0;
hilo->contexto_hilo->HX = 0;

leer_intrucciones (archivo_instrucciones, hilo->instrucciones);


}

void leer_intrucciones (char* path, t_list* lista_instrucciones) {
 FILE *f = fopen(path, "r");
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
//        log_info(logger, "Instrucción cargada=> %s - Proceso %d", instrucciones_split[i], process);
        i++;
    }

    fclose(f);
    }