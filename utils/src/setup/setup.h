#ifndef SETUP_H_
#define SETUP_H_

#include<stdio.h>
#include<stdlib.h>

#include<commons/log.h>
#include<commons/config.h>

#include <errno.h>
#include <commons/error.h>

// ---------------------------------------------------------------------------------------

// Generar e iniciar configuracion del modulo.
t_config* iniciar_config(char* modulo, char* path);
// Generar e iniciar logger del modulo.
t_log* iniciar_logger(char* modulo, char* path, char* log_level);
// Verificar existencia de la KEY.
void verificarKEY(t_config* config, char* KEY);
// Iniciar modulo.
void iniciar_modulo(char* modulo, char* path_log, char* path_config, t_log** logger, t_config** config);
// Finalizar modulo.
void finalizar_modulo(char* modulo, t_log** logger, t_config** config);

#endif