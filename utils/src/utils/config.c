#include <utils/config.h>

t_config *iniciar_config(char *archivo)
{
	t_config *nuevo_config;

	nuevo_config = config_create(archivo);

	if (nuevo_config == NULL)
	{
		exit(EXIT_FAILURE);
	}

	return nuevo_config;
}