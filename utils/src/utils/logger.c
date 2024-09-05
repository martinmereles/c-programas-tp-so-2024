#include <utils/logger.h>

t_log *iniciar_logger(char *archivo, char *nombre)
{
    t_log *logger_nuevo = log_create(archivo, nombre, true, LOG_LEVEL_INFO);

    return logger_nuevo;
}