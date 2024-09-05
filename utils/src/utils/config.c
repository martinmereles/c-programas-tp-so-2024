#include <utils/config.h>

t_config *iniciar_config(t_log *logger, char *archivo)
{
	t_config *nuevo_config;

	nuevo_config = config_create(archivo);

	if (nuevo_config == NULL)
	{
		log_info(logger, "No existe el archivo %s", archivo);
		exit(EXIT_FAILURE);
	}

	return nuevo_config;
}