#include <utils/logger.h>

t_log *iniciar_logger(char *archivo, char *nombre, char* log_level_string)
{
    t_log_level log_level = log_level_from_string(log_level_string);
    t_log *logger_nuevo = log_create(archivo, nombre, true, log_level);

    return logger_nuevo;
}