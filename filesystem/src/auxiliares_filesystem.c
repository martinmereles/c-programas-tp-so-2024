#include <../include/auxiliares_filesystem.h>

void iniciar_fs()
{
    char *path_fs_bloques = string_new();
    char *path_fs_bitmap = string_new();
    char *path_fs_files = string_new();
    string_append(&path_fs_bloques, mount_dir);
    string_append(&path_fs_bitmap, mount_dir);
    string_append(&path_fs_files, mount_dir);
    string_append(&path_fs_bloques, "/bloques.dat");
    string_append(&path_fs_bitmap, "/bitmap.dat");
    string_append(&path_fs_files, "/files");

    FILE *file_bitmap = fopen(path_fs_bitmap, "r+");
    FILE *file_bloques = fopen(path_fs_bloques, "r+");

    if (file_bitmap == NULL || file_bloques == NULL)
    {
        file_bloques = fopen(path_fs_bloques, "w+");
        file_bitmap = fopen(path_fs_bitmap, "w+");

        // Inicializo bitmap
        void *bitmap = malloc(block_count / 8);
        sem_wait(&fs_en_uso);
        bitmap_bloques_libres = bitarray_create_with_mode(bitmap, block_count / 8, LSB_FIRST);
        for (int i = 0; i < block_count; i++)
        {
            bitarray_clean_bit(bitmap_bloques_libres, i);
        }
        fwrite(bitmap_bloques_libres->bitarray, bitmap_bloques_libres->size, 1, file_bitmap);

        // Inicializo bloques
        void *bloques = calloc(block_count, block_size);
        fwrite(bloques, block_size, block_count, file_bloques);
        sem_post(&fs_en_uso);
        fclose(file_bitmap);
        fclose(file_bloques);
    }
    else
    {
        fseek(file_bitmap, 0L, SEEK_END);
        int sz = ftell(file_bitmap);
        rewind(file_bitmap);

        void *bitmap = malloc(block_count / 8);
        sem_wait(&fs_en_uso);
        bitmap_bloques_libres = bitarray_create_with_mode(bitmap, block_count / 8, LSB_FIRST);
        fread(bitmap_bloques_libres->bitarray, sz, 1, file_bitmap);
        sem_post(&fs_en_uso);
        fclose(file_bitmap);
        fclose(file_bloques);
    }

    DIR *directorio_file = opendir(path_fs_files);
    if (directorio_file == NULL)
    {
        mkdir(path_fs_files, 0777);
    }
    closedir(directorio_file);
}

void fs_create(char *nombre_archivo, int tamanio, void *contenido, int socket_memoria)
{
    sem_wait(&fs_en_uso);
    // Verificamos si hay espacio
    int cantidad_bloques_necesarios = calcular_cantidad_bloques(tamanio);
    int cantidad_bloques_libres = calcular_bloques_libres();
    if (cantidad_bloques_necesarios > cantidad_bloques_libres)
    {
        char** nombre_split = string_split(nombre_archivo, "-");
        sem_post(&fs_en_uso);
        char* mensaje_memoria = string_new();
        string_append(&mensaje_memoria, "DUMP_MEMORY_FAIL");
        string_append(&mensaje_memoria, " ");
        string_append(&mensaje_memoria, nombre_split[0]);
        string_append(&mensaje_memoria, " ");
        string_append(&mensaje_memoria, nombre_split[1]);
        enviar_mensaje(mensaje_memoria, socket_memoria);
        return;
    }

    // Reservamos bloques
    t_list *bloques_reservados = list_create();
    int proximo_bloque;
    for (int i = 0; i < cantidad_bloques_necesarios; i++)
    {

        proximo_bloque = primer_bloque_libre();
        list_add(bloques_reservados, proximo_bloque);
        set_bloque_usado(proximo_bloque);
        log_info(logger, "## Bloque asignado: %d - Archivo: %s - Bloques Libres: %d", proximo_bloque, nombre_archivo, calcular_bloques_libres());
    }

    // Creamos el metadata
    char *path_metadata = string_new();
    string_append(&path_metadata, mount_dir);
    string_append(&path_metadata, "/files/");
    string_append(&path_metadata, nombre_archivo);
    string_append(&path_metadata, ".dmp");
    char *text_bloque_index = string_new();
    char *text_tamanio = string_new();
    string_append(&text_bloque_index, "INDEX_BLOCK=");
    string_append(&text_tamanio, "SIZE=");
    string_append(&text_bloque_index, string_itoa(list_get(bloques_reservados, 0)));
    string_append(&text_tamanio, string_itoa(tamanio));
    FILE *metadata = txt_open_for_append(path_metadata);
    txt_write_in_file(metadata, text_tamanio);
    txt_write_in_file(metadata, "\n");
    txt_write_in_file(metadata, text_bloque_index);
    txt_close_file(metadata);

    // Grabamos bloque de punteros
    int bloque_index = list_remove(bloques_reservados, 0);
    int cantidad_punteros_por_bloque = block_size / 4;
    char *path_bloques = string_new();
    string_append(&path_bloques, mount_dir);
    string_append(&path_bloques, "/bloques.dat");
    FILE *file_bloques = fopen(path_bloques, "r+");
    fseek(file_bloques, block_size * bloque_index, SEEK_SET);
    uint32_t puntero_a_escribir;
    t_list *bloques_datos = list_duplicate(bloques_reservados);
    for (int i = 0; i < cantidad_punteros_por_bloque; i++)
    {
        if (list_is_empty(bloques_reservados))
        {
            puntero_a_escribir = -1;
            fwrite(&puntero_a_escribir, sizeof(puntero_a_escribir), 1, file_bloques);
        }
        else
        {
            puntero_a_escribir = list_remove(bloques_reservados, 0);
            fwrite(&puntero_a_escribir, sizeof(uint32_t), 1, file_bloques);
        }
    }
    usleep(retardo * 1000);
    log_info(logger, "## Acceso Bloque - Archivo: %s - Tipo Bloque: ÍNDICE - Bloque File System %d", nombre_archivo, bloque_index);

    // Grabamos bloques de datos
    int bloque_dato;
    unsigned char *restante = (unsigned char *)contenido;
    char *a_escribir;
    while (!list_is_empty(bloques_datos))
    {

        if (string_length(restante) > block_size)
        {
            a_escribir = string_substring(restante, 0, block_size);
            restante = string_substring_from(restante, block_size);
        }
        else
        {
            a_escribir = restante;
        }

        bloque_dato = list_remove(bloques_datos, 0);
        fseek(file_bloques, block_size * bloque_dato, SEEK_SET);
        fwrite(a_escribir, string_length(a_escribir), 1, file_bloques);
        usleep(retardo * 1000);

        log_info(logger, "## Acceso Bloque - Archivo: %s - Tipo Bloque: DATOS - Bloque File System %d", nombre_archivo, bloque_dato);
    }
    fclose(file_bloques);
    list_destroy(bloques_reservados);
    list_destroy(bloques_datos);
    sem_post(&fs_en_uso);
    log_info(logger, "## Archivo Creado: %s - Tamaño: %d", nombre_archivo, tamanio);
    char** nombre_split = string_split(nombre_archivo, "-");
    char* mensaje_memoria = string_new();
    string_append(&mensaje_memoria, "DUMP_MEMORY_SUCCESS");
    string_append(&mensaje_memoria, " ");
    string_append(&mensaje_memoria, nombre_split[0]);
    string_append(&mensaje_memoria, " ");
    string_append(&mensaje_memoria, nombre_split[1]);
    enviar_mensaje(mensaje_memoria, socket_memoria);
    log_info(logger, "## Fin de solicitud - Archivo: %s", nombre_archivo);
}

int calcular_cantidad_bloques(int tamanio)
{
    double cantidad = ceil((double)tamanio / (double)block_size);
    cantidad++;
    return cantidad;
}

int calcular_bloques_libres()
{
    int cantidad_total_bloques_libres = 0;
    for (int i = 0; bitmap_bloques_libres->size * 8 > i; i++)
    {
        if (!bitarray_test_bit(bitmap_bloques_libres, i))
        {
            cantidad_total_bloques_libres++;
        }
    }
    return cantidad_total_bloques_libres;
}

void set_bloque_usado(int posicion)
{
    char *path_fs_bitmap = string_new();
    string_append(&path_fs_bitmap, mount_dir);
    string_append(&path_fs_bitmap, "/bitmap.dat");
    FILE *file_bitmap = fopen(path_fs_bitmap, "r+");
    bitarray_set_bit(bitmap_bloques_libres, posicion);
    fwrite(bitmap_bloques_libres->bitarray, bitmap_bloques_libres->size, 1, file_bitmap);
    fclose(file_bitmap);
}

void set_bloque_libre(int posicion)
{
    char *path_fs_bitmap = string_new();
    string_append(&path_fs_bitmap, mount_dir);
    string_append(&path_fs_bitmap, "/bitmap.dat");
    FILE *file_bitmap = fopen(path_fs_bitmap, "r+");
    bitarray_clean_bit(bitmap_bloques_libres, posicion);
    fwrite(bitmap_bloques_libres->bitarray, bitmap_bloques_libres->size, 1, file_bitmap);
    fclose(file_bitmap);
}

int primer_bloque_libre()
{
    int posicion = 0;
    while (bitarray_test_bit(bitmap_bloques_libres, posicion) && posicion < (bitmap_bloques_libres->size * 8 - 1))
    {
        posicion++;
    }

    if (posicion >= (bitmap_bloques_libres->size * 8 - 1))
    {
        posicion = -1;
    }
    return posicion;
}

pthread_t iniciar_hilo_server_fs(char *puerto)
{
    int socket_servidor = iniciar_servidor(puerto);

    pthread_t hiloAtencion;
    pthread_create(&hiloAtencion,
                   NULL,
                   (void *)hilo_cliente_fs,
                   socket_servidor);

    return hiloAtencion;
}

void hilo_cliente_fs(int socket_servidor)
{
    while (1)
    {

        int socket_cliente = esperar_cliente(socket_servidor);
        pthread_t hiloCliente;
        pthread_create(&hiloCliente,
                       NULL,
                       (void *)atender_cliente_fs,
                       socket_cliente);
        pthread_detach(hiloCliente);
    }
}

void atender_cliente_fs(int socket_cliente)
{
    int cod_op;
    int size;
    char *buffer;
    t_list *lista;

    t_atencion_mensaje *param_atencion_mensaje = malloc(sizeof(t_atencion_mensaje));
    t_atencion_paquete *param_atencion_paquete = malloc(sizeof(t_atencion_paquete));
    while (1)
    {
        cod_op = recibir_operacion(socket_cliente);
        switch (cod_op)
        {
        case MENSAJE:
            buffer = recibir_buffer(&size, socket_cliente);

            param_atencion_mensaje->buffer = buffer;
            param_atencion_mensaje->socket_cliente = socket_cliente;
            pthread_t hiloAtencionMensaje;
            pthread_create(&hiloAtencionMensaje,
                           NULL,
                           (void *)entender_mensaje_filesystem,
                           param_atencion_mensaje);
            pthread_detach(hiloAtencionMensaje);

            break;
        case PAQUETE:

            lista = recibir_paquete(socket_cliente);

            param_atencion_paquete->lista = lista;
            param_atencion_paquete->socket_cliente = socket_cliente;
            pthread_t hiloAtencionPaquete;
            pthread_create(&hiloAtencionPaquete,
                           NULL,
                           (void *)entender_paquete_filesystem,
                           param_atencion_paquete);
            pthread_detach(hiloAtencionPaquete);
            break;
        case -1:
            log_error(logger, "El cliente se desconecto.");
            return EXIT_FAILURE;
        default:
            log_warning(logger, "Operacion desconocida. No quieras meter la pata.");
            break;
        }
    }
}

void entender_mensaje_filesystem(t_atencion_mensaje *param_atencion)
{
    char *buffer = param_atencion->buffer;
    int socket_cliente = param_atencion->socket_cliente;

    char **mensaje_split = string_split(buffer, " ");

    log_info(logger, "Me llego el mensaje %s", buffer);

    free(buffer);
}

void entender_paquete_filesystem(t_atencion_paquete *param_atencion)
{
    t_list *lista = param_atencion->lista;
    int socket_cliente = param_atencion->socket_cliente;

    if (string_starts_with(list_get(lista, 0), "DUMP_MEMORY"))
    {
        fs_create(list_get(lista, 1), atoi(list_get(lista, 2)), list_get(lista, 3), socket_cliente);
    }
}