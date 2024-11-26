#ifndef _AUXILIARES_FILESYSTEM_H_
#define _AUXILIARES_FILESYSTEM_H_

#include <utils/estructuras.h>
#include <commons/string.h>
#include <utils/client-server.h>
#include <commons/bitarray.h>
#include <commons/txt.h>
#include <dirent.h>
#include <math.h>

extern t_log* logger;
extern t_config* config;
extern char* mount_dir;
extern int block_size;
extern int block_count;
extern int retardo;
extern sem_t fs_en_uso;
extern t_bitarray* bitmap_bloques_libres;

void iniciar_fs();
void fs_create(char *nombre_archivo, int tamanio, void* contenido,int socket_memoria);
int calcular_cantidad_bloques(int tamanio);
int calcular_bloques_libres();
void set_bloque_usado(int posicion);
void set_bloque_libre(int posicion);
int primer_bloque_libre();
void atender_cliente_fs(int socket_cliente);
void hilo_cliente_fs(int socket_servidor);
pthread_t iniciar_hilo_server_fs(char *puerto);
void entender_mensaje_filesystem(t_atencion_mensaje *param_atencion);
void entender_paquete_filesystem(t_atencion_paquete *param_atencion);

#endif