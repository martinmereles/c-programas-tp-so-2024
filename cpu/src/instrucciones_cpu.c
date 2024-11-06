#include <../include/instrucciones_cpu.h>

/*----------------------------------SET DE INSTRUCCIONES---------------------------------*/
void set(char *registro, char *valor)
{

    int valorASetear = atoi(valor);

    if (strcmp(registro, "PC") == 0)
    {
        PC = valorASetear;
    }
    if (strcmp(registro, "AX") == 0)
    {
        AX = valorASetear;
    }
    if (strcmp(registro, "BX") == 0)
    {
        BX = valorASetear;
    }
    if (strcmp(registro, "CX") == 0)
    {
        CX = valorASetear;
    }
    if (strcmp(registro, "DX") == 0)
    {
        DX = valorASetear;
    }
    if (strcmp(registro, "EX") == 0)
    {
        EX = valorASetear;
    }
    if (strcmp(registro, "FX") == 0)
    {
        FX = valorASetear;
    }
    if (strcmp(registro, "GX") == 0)
    {
        GX = valorASetear;
    }
    if (strcmp(registro, "HX") == 0)
    {
        HX = valorASetear;
    }
    if (strcmp(registro, "BASE") == 0)
    {
        BASE = valorASetear;
    }
    if (strcmp(registro, "LIMITE") == 0)
    {
        LIMITE = valorASetear;
    }

    log_info(logger, "##TID: %d - Ejecutando: SET - %s %s", tid, registro, valor);
}

void read_mem(char *registro_datos, char *registro_direccion)
{
    // TO DO Pasar a decode
    // Lee el valor de memoria correspondiente a la Dirección Lógica
    // que se encuentra en el Registro Dirección y lo almacena en el Registro Datos.
    int valor_registro_direccion = get_valor_registro(registro_direccion);
    if(validar_direccion(valor_registro_direccion) != 0)
    {
        //Segmentation fault
        //Mensaje a memoria para actualizar contexto
        crear_paquete_contexto();
        //Mensaje a Kernel con tid con motivo segmentation fault
        char* mensaje = string_new();
        string_append(&mensaje,"SEGMENTATION_FAULT ");
        string_append(&mensaje, tid);
        enviar_mensaje(mensaje ,socket_kernel_dispatch);
    }
    //Leer de Registro direccion

    log_info(logger, "##TID: %d - Acción: LEER - Dirección Física: %d", tid, valor_registro_direccion);

    log_info(logger, "##TID: %d - Ejecutando: READ_MEM - %s %s", tid, registro_datos, registro_direccion);
}

void write_mem(char *registro_direccion, char *registro_datos)
{
    // TO DO Pasar a decode
    // Lee el valor del Registro Datos y lo escribe en la dirección
    // física de memoria obtenida a partir de la Dirección Lógica almacenada en el Registro Dirección.
    int valor_registro_direccion = get_valor_registro(registro_direccion);
    if(validar_direccion(valor_registro_direccion) != 0)
    {
        //Segmentation fault
        //Mensaje a memoria para actualizar contexto
        crear_paquete_contexto();
        //Mensaje a Kernel con tid con motivo segmentation fault
        char* mensaje = string_new();
        string_append(&mensaje,"SEGMENTATION_FAULT ");
        string_append(&mensaje, tid);
        enviar_mensaje(mensaje ,socket_kernel_dispatch);
    }
    //escribir en la direccion

    log_info(logger, "##TID: %d - Acción: ESCRIBIR - Dirección Física: %d", tid, valor_registro_direccion);

    log_info(logger, "##TID: %d - Ejecutando: WRITE_MEM - %s %s", tid, registro_direccion, registro_datos);
}

void sum(char *registro_destino, char *registro_origen)
{
    if (strcmp(registro_destino, "PC") == 0)
    {   
        if (strcmp(registro_origen, "PC") == 0)
        {
            PC += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            PC += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            PC += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            PC += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            PC += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            PC += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            PC += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            PC += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            PC += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            PC += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            PC += LIMITE;
        }
    }
    if (strcmp(registro_destino, "AX") == 0)
    {   
        if (strcmp(registro_origen, "PC") == 0)
        {
            AX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            AX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            AX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            AX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            AX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            AX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            AX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            AX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            AX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            AX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            AX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "BX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            BX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            BX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            BX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            BX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            BX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            BX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            BX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            BX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            BX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            BX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            BX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "CX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            CX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            CX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            CX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            CX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            CX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            CX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            CX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            CX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            CX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            CX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            CX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "DX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            DX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            DX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            DX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            DX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            DX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            DX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            DX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            DX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            DX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            DX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            DX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "EX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            EX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            EX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            EX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            EX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            EX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            EX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            EX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            EX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            EX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            EX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            EX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "FX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            FX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            FX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            FX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            FX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            FX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            FX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            FX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            FX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            FX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            FX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            FX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "GX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            GX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            GX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            GX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            GX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            GX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            GX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            GX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            GX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            GX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            GX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            GX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "HX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            HX += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            HX += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            HX += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            HX += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            HX += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            HX += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            HX += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            HX += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            HX += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            HX += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            HX += LIMITE;
        }
    }
    if (strcmp(registro_destino, "BASE") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            BASE += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            BASE += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            BASE += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            BASE += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            BASE += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            BASE += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            BASE += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            BASE += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            BASE += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            BASE += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            BASE += LIMITE;
        }
    }
    if (strcmp(registro_destino, "LIMITE") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            LIMITE += PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            LIMITE += AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            LIMITE += BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            LIMITE += CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            LIMITE += DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            LIMITE += EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            LIMITE += FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            LIMITE += GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            LIMITE += HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            LIMITE += BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            LIMITE += LIMITE;
        }
    }

    log_info(logger, "##tID: %d - Ejecutando: SUM - %s %s", tid, registro_destino, registro_origen);
}

void sub(char *registro_destino, char *registro_origen)
{   
    if (strcmp(registro_destino, "PC") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            PC -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            PC -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            PC -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            PC -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            PC -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            PC -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            PC -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            PC -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            PC -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            PC -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            PC -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "AX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            AX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            AX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            AX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            AX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            AX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            AX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            AX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            AX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            AX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            AX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            AX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "BX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            BX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            BX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            BX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            BX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            BX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            BX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            BX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            BX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            BX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            BX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            BX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "CX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            CX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            CX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            CX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            CX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            CX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            CX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            CX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            CX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            CX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            CX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            CX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "DX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            DX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            DX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            DX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            DX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            DX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            DX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            DX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            DX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            DX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            DX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            DX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "EX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            EX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            EX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            EX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            EX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            EX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            EX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            EX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            EX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            EX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            EX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            EX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "FX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            FX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            FX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            FX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            FX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            FX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            FX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            FX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            FX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            FX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            FX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            FX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "GX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            GX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            GX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            GX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            GX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            GX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            GX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            GX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            GX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            GX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            GX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            GX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "HX") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            HX -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            HX -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            HX -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            HX -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            HX -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            HX -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            HX -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            HX -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            HX -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            HX -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            HX -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "BASE") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            BASE -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            BASE -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            BASE -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            BASE -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            BASE -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            BASE -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            BASE -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            BASE -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            BASE -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            BASE -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            BASE -= LIMITE;
        }
    }
    if (strcmp(registro_destino, "LIMITE") == 0)
    {
        if (strcmp(registro_origen, "PC") == 0)
        {
            LIMITE -= PC;
        }
        if (strcmp(registro_origen, "AX") == 0)
        {
            LIMITE -= AX;
        }
        if (strcmp(registro_origen, "BX") == 0)
        {
            LIMITE -= BX;
        }
        if (strcmp(registro_origen, "CX") == 0)
        {
            LIMITE -= CX;
        }
        if (strcmp(registro_origen, "DX") == 0)
        {
            LIMITE -= DX;
        }
        if (strcmp(registro_origen, "EX") == 0)
        {
            LIMITE -= EX;
        }
        if (strcmp(registro_origen, "FX") == 0)
        {
            LIMITE -= FX;
        }
        if (strcmp(registro_origen, "GX") == 0)
        {
            LIMITE -= GX;
        }
        if (strcmp(registro_origen, "HX") == 0)
        {
            LIMITE -= HX;
        }
        if (strcmp(registro_origen, "BASE") == 0)
        {
            LIMITE -= BASE;
        }
        if (strcmp(registro_origen, "LIMITE") == 0)
        {
            LIMITE -= LIMITE;
        }
    }
    
    log_info(logger, "##PID: %d - Ejecutando: SUB - %s %s", tid, registro_destino, registro_origen);
}

void jnz(char *registro, char *instruccion)
{

    int valorASetear = atoi(instruccion);

    if (strcmp(registro, "AX") == 0 && AX != 0)
    {   
        AX = valorASetear;
    }
    if (strcmp(registro, "BX") == 0 && BX != 0)
    {   
        BX = valorASetear;
    }
    if (strcmp(registro, "CX") == 0 && CX != 0)
    {   
        CX = valorASetear;
    }
    if (strcmp(registro, "DX") == 0 && DX != 0)
    {   
        DX = valorASetear;
    }
    if (strcmp(registro, "EX") == 0 && EX != 0)
    {   
        EX = valorASetear;
    }
    if (strcmp(registro, "FX") == 0 && FX != 0)
    {   
        FX = valorASetear;
    }
    if (strcmp(registro, "GX") == 0 && GX != 0)
    {   
        GX = valorASetear;
    }
    if (strcmp(registro, "HX") == 0 && HX != 0)
    {   
        HX = valorASetear;
    }
    if (strcmp(registro, "BASE") == 0 && BASE != 0)
    {   
        BASE = valorASetear;
    }
    if (strcmp(registro, "LIMITE") == 0 && LIMITE != 0)
    {   
        LIMITE = valorASetear;
    }
    if (strcmp(registro, "PC") == 0 && PC != 0)
    {   
        PC = valorASetear;
    }
    
    log_info(logger, "##TID: %d - Ejecutando: JNZ - %s %s", tid, registro, instruccion);
}

void log(char *registro)
{
    // TO DO
    // Escribe en el archivo de log el valor del registro.
    int valor_a_guardar;

    if (strcmp(registro, "AX") == 0)
    {   
        valor_a_guardar = AX;
    }
    if (strcmp(registro, "BX") == 0)
    {   
        valor_a_guardar = BX;
    }
    if (strcmp(registro, "CX") == 0)
    {   
        valor_a_guardar = CX;
    }
    if (strcmp(registro, "DX") == 0)
    {   
        valor_a_guardar = DX;
    }
    if (strcmp(registro, "EX") == 0)
    {   
        valor_a_guardar = EX;
    }
    if (strcmp(registro, "FX") == 0)
    {   
        valor_a_guardar = FX;
    }
    if (strcmp(registro, "GX") == 0)
    {   
        valor_a_guardar = GX;
    }
    if (strcmp(registro, "HX") == 0)
    {   
        valor_a_guardar = HX;
    }
    if (strcmp(registro, "BASE") == 0)
    {   
        valor_a_guardar = BASE;
    }
    if (strcmp(registro, "LIMITE") == 0)
    {   
        valor_a_guardar = LIMITE;
    }
    if (strcmp(registro, "PC") == 0)
    {   
        valor_a_guardar = PC;
    }

    log_info(logger, "##TID: %d - Ejecutando: LOG - %s", tid, registro);
}

void ejecutarSentencia(int socket_cliente_memoria)
{

    char *instruccion_exec;
    char **sentenciasSplit = string_split(instruccion_exec, " ");
    if (strcmp(sentenciasSplit[0], "SET") == 0)
    {
        set(sentenciasSplit[1], sentenciasSplit[2]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "READ_MEM") == 0)
    {
        read_mem(sentenciasSplit[1], sentenciasSplit[2]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "WRITE_MEM") == 0)
    {
        write_mem(sentenciasSplit[1], sentenciasSplit[2]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "SUM") == 0)
    {
        sum(sentenciasSplit[1], sentenciasSplit[2]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "SUB") == 0)
    {
        sub(sentenciasSplit[1], sentenciasSplit[2]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "JNZ") == 0)
    {
        jnz(sentenciasSplit[1], sentenciasSplit[2]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "LOG") == 0)
    {
        log(sentenciasSplit[1]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "PROCESS_CREATE") == 0)
    {
        process_create(sentenciasSplit[1], sentenciasSplit[2], sentenciasSplit[3]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "PROCESS_EXIT") == 0)
    {
        process_exit();
        return;
    }
    if (strcmp(sentenciasSplit[0], "THREAD_CREATE") == 0)
    {
        thread_create(sentenciasSplit[1], sentenciasSplit[2]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "THREAD_JOIN") == 0)
    {
        thread_join(sentenciasSplit[1]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "THREAD_CANCEL") == 0)
    {
        thread_cancel(sentenciasSplit[1]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "THREAD_EXIT") == 0)
    {
        thread_exit();
        return;
    }
    if (strcmp(sentenciasSplit[0], "MUTEX_CREATE") == 0)
    {
        mutex_create(sentenciasSplit[1]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "MUTEX_LOCK") == 0)
    {
        mutex_lock(sentenciasSplit[1]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "MUTEX_UNLOCK") == 0)
    {
        mutex_unlock(sentenciasSplit[1]);
        return;
    }
    if (strcmp(sentenciasSplit[0], "DUMP_MEMORY") == 0)
    {
        dump_memory();
        return;
    }
    if (strcmp(sentenciasSplit[0], "IO") == 0)
    {
        io(sentenciasSplit[1]);
        return;
    }
}