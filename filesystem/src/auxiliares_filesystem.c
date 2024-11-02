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
    if (directorio_file == NULL) {
        mkdir(path_fs_files, 0777);
    }
    closedir(directorio_file);
}

void fs_create(char *nombre_archivo, int tamanio, void* contenido)
{

    //Verificar si hay espacio

    
}