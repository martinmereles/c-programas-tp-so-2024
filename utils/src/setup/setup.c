#include <setup/setup.h>

t_config* iniciar_config(char* modulo, char* path) {
    // Generar las configuraciones.
    t_config* config = config_create(path);

    // Verificar si se ha generado correctamente.
    if(config == NULL) {
        // Mostrar mensaje de error por consola.
        error_show("Error al iniciar las configuraciones del modulo %s", modulo);
        // Abortar programa.
        abort();
    }

    // Retornar las configuraciones iniciadas.
    return config;
}

t_log* iniciar_logger(char* modulo, char* path, char* log_level) {
    // Crear instancia de logger.
    t_log* logger = log_create(path, modulo, 1, log_level_from_string(log_level));

    // Verificar si se ha creado correctamente.
    if(logger == NULL) {
        // Mostrar mensaje de error por consola.
        error_show("Error al iniciar instancia de logger del modulo %s", modulo);
        // Abortar programa.
        abort();
    }

    // Loggear inicio de la instancia de logger.
    log_info(logger, "Iniciado modulo %s...", modulo);

    // Retornar instancia de logger.
    return logger;
}

void verificar_KEY(t_config* config, char* KEY) {
    // Verificar la existencia de la KEY "LOG_LEVEL" en la config.
    if(!config_has_property(config, KEY)) {
        // Mostrar mensaje de error por consola.d
        error_show("Error en la existencia de la KEY '%s'", KEY);
        // Abortar programa.
        abort();
    }
}

void iniciar_modulo(char* modulo, char* path_log, char* path_config, t_log** logger, t_config** config) {
    // Generar e iniciar las configuraciones.
    *config = iniciar_config(modulo, path_config);

    // Verificar la existencia de la KEY "LOG_LEVEL" en la config.
    verificar_KEY(*config, "LOG_LEVEL");

    // Crear e iniciar instancia de logger.
    *logger = iniciar_logger(modulo, path_log, config_get_string_value(*config, "LOG_LEVEL"));
    
    // Loggear inicio de la instancia de logger.
    log_info(*logger, "Se ha iniciado el modulo %s correctamente.", modulo);
}

void finalizar_modulo(char* modulo, t_log** logger, t_config** config) {
    // Loggear finalizacion del modulo.
    log_info(*logger, "Finalizando modulo %s...\n", modulo);

    // Si existe un log, lo destruimos.
    if(logger != NULL) log_destroy(*logger);
    // Si existe una config, lo detruimos.
    if(config != NULL) config_destroy(*config);
}