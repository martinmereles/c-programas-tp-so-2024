#ifndef _AUXILIARES_FILESYSTEM_H_
#define _AUXILIARES_FILESYSTEM_H_

#include <utils/estructuras.h>
#include <commons/string.h>
#include <utils/client-server.h>
#include <commons/bitarray.h>

#include <dirent.h>

extern t_log* logger;
extern t_config* config;
extern char* mount_dir;
extern int block_size;
extern int block_count;
extern int retardo;
extern t_log_level log_level;
extern sem_t fs_en_uso;
extern t_bitarray* bitmap_bloques_libres;

void iniciar_fs();
void fs_create(char *nombre_archivo, int tamanio, void* contenido);

#endif