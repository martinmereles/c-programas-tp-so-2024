#ifndef UTILS_CONFIG_H_
#define UTILS_CONFIG_H_

#include <stdlib.h>
#include <stdio.h>
#include <commons/config.h>
#include <commons/log.h>

t_config *iniciar_config(char *archivo);

extern t_log* logger;

#endif