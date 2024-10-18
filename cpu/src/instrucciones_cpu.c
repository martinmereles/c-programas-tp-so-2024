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
    // TO DO
    // Lee el valor de memoria correspondiente a la Dirección Lógica
    // que se encuentra en el Registro Dirección y lo almacena en el Registro Datos.
}

void write_mem(char *registro_direccion, char *registro_datos)
{
    // TO DO
    // Lee el valor del Registro Datos y lo escribe en la dirección
    // física de memoria obtenida a partir de la Dirección Lógica almacenada en el Registro Dirección.
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
    if (registro_destino == "FX")
    {
        if (registro_origen == "PC")
        {
            FX += PC;
        }
        if (registro_origen == "AX")
        {
            FX += AX;
        }
        if (registro_origen == "BX")
        {
            FX += BX;
        }
        if (registro_origen == "CX")
        {
            FX += CX;
        }
        if (registro_origen == "DX")
        {
            FX += DX;
        }
        if (registro_origen == "EX")
        {
            FX += EX;
        }
        if (registro_origen == "FX")
        {
            FX += FX;
        }
        if (registro_origen == "GX")
        {
            FX += GX;
        }
        if (registro_origen == "HX")
        {
            FX += HX;
        }
        if (registro_origen == "BASE")
        {
            FX += BASE;
        }
        if (registro_origen == "LIMITE")
        {
            FX += LIMITE;
        }
    }
    if (registro_destino == "GX")
    {
        if (registro_origen == "PC")
        {
            GX += PC;
        }
        if (registro_origen == "AX")
        {
            GX += AX;
        }
        if (registro_origen == "BX")
        {
            GX += BX;
        }
        if (registro_origen == "CX")
        {
            GX += CX;
        }
        if (registro_origen == "DX")
        {
            GX += DX;
        }
        if (registro_origen == "EX")
        {
            GX += EX;
        }
        if (registro_origen == "FX")
        {
            GX += FX;
        }
        if (registro_origen == "GX")
        {
            GX += GX;
        }
        if (registro_origen == "HX")
        {
            GX += HX;
        }
        if (registro_origen == "BASE")
        {
            GX += BASE;
        }
        if (registro_origen == "LIMITE")
        {
            GX += LIMITE;
        }
    }
    if (registro_destino == "HX")
    {
        if (registro_origen == "PC")
        {
            HX += PC;
        }
        if (registro_origen == "AX")
        {
            HX += AX;
        }
        if (registro_origen == "BX")
        {
            HX += BX;
        }
        if (registro_origen == "CX")
        {
            HX += CX;
        }
        if (registro_origen == "DX")
        {
            HX += DX;
        }
        if (registro_origen == "EX")
        {
            HX += EX;
        }
        if (registro_origen == "FX")
        {
            HX += FX;
        }
        if (registro_origen == "GX")
        {
            HX += GX;
        }
        if (registro_origen == "HX")
        {
            HX += HX;
        }
        if (registro_origen == "BASE")
        {
            HX += BASE;
        }
        if (registro_origen == "LIMITE")
        {
            HX += LIMITE;
        }
    }
    if (registro_destino == "BASE")
    {
        if (registro_origen == "PC")
        {
            BASE += PC;
        }
        if (registro_origen == "AX")
        {
            BASE += AX;
        }
        if (registro_origen == "BX")
        {
            BASE += BX;
        }
        if (registro_origen == "CX")
        {
            BASE += CX;
        }
        if (registro_origen == "DX")
        {
            BASE += DX;
        }
        if (registro_origen == "EX")
        {
            BASE += EX;
        }
        if (registro_origen == "FX")
        {
            BASE += FX;
        }
        if (registro_origen == "GX")
        {
            BASE += GX;
        }
        if (registro_origen == "HX")
        {
            BASE += HX;
        }
        if (registro_origen == "BASE")
        {
            BASE += BASE;
        }
        if (registro_origen == "LIMITE")
        {
            BASE += LIMITE;
        }
    }
    if (registro_destino == "LIMITE")
    {
        if (registro_origen == "PC")
        {
            LIMITE += PC;
        }
        if (registro_origen == "AX")
        {
            LIMITE += AX;
        }
        if (registro_origen == "BX")
        {
            LIMITE += BX;
        }
        if (registro_origen == "CX")
        {
            LIMITE += CX;
        }
        if (registro_origen == "DX")
        {
            LIMITE += DX;
        }
        if (registro_origen == "EX")
        {
            LIMITE += EX;
        }
        if (registro_origen == "FX")
        {
            LIMITE += FX;
        }
        if (registro_origen == "GX")
        {
            LIMITE += GX;
        }
        if (registro_origen == "HX")
        {
            LIMITE += HX;
        }
        if (registro_origen == "BASE")
        {
            LIMITE += BASE;
        }
        if (registro_origen == "LIMITE")
        {
            LIMITE += LIMITE;
        }
    }

    log_info(logger, "##tID: %d - Ejecutando: SUM - %s %s", tid, registro_destino, registro_origen);
}

void sub(char *registro_destino, char *registro_origen)
{   
    if (registro_destino == "PC")
    {
        if (registro_origen == "PC")
        {
            PC -= PC;
        }
        if (registro_origen == "AX")
        {
            PC -= AX;
        }
        if (registro_origen == "BX")
        {
            PC -= BX;
        }
        if (registro_origen == "CX")
        {
            PC -= CX;
        }
        if (registro_origen == "DX")
        {
            PC -= DX;
        }
        if (registro_origen == "EX")
        {
            PC -= EX;
        }
        if (registro_origen == "FX")
        {
            PC -= FX;
        }
        if (registro_origen == "GX")
        {
            PC -= GX;
        }
        if (registro_origen == "HX")
        {
            PC -= HX;
        }
        if (registro_origen == "BASE")
        {
            PC -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            PC -= LIMITE;
        }
    }
    if (registro_destino == "AX")
    {
        if (registro_origen == "PC")
        {
            AX -= PC;
        }
        if (registro_origen == "AX")
        {
            AX -= AX;
        }
        if (registro_origen == "BX")
        {
            AX -= BX;
        }
        if (registro_origen == "CX")
        {
            AX -= CX;
        }
        if (registro_origen == "DX")
        {
            AX -= DX;
        }
        if (registro_origen == "EX")
        {
            AX -= EX;
        }
        if (registro_origen == "FX")
        {
            AX -= FX;
        }
        if (registro_origen == "GX")
        {
            AX -= GX;
        }
        if (registro_origen == "HX")
        {
            AX -= HX;
        }
        if (registro_origen == "BASE")
        {
            AX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            AX -= LIMITE;
        }
    }
    if (registro_destino == "BX")
    {
        if (registro_origen == "PC")
        {
            BX -= PC;
        }
        if (registro_origen == "AX")
        {
            BX -= AX;
        }
        if (registro_origen == "BX")
        {
            BX -= BX;
        }
        if (registro_origen == "CX")
        {
            BX -= CX;
        }
        if (registro_origen == "DX")
        {
            BX -= DX;
        }
        if (registro_origen == "EX")
        {
            BX -= EX;
        }
        if (registro_origen == "FX")
        {
            BX -= FX;
        }
        if (registro_origen == "GX")
        {
            BX -= GX;
        }
        if (registro_origen == "HX")
        {
            BX -= HX;
        }
        if (registro_origen == "BASE")
        {
            BX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            BX -= LIMITE;
        }
    }
    if (registro_destino == "CX")
    {
        if (registro_origen == "PC")
        {
            CX -= PC;
        }
        if (registro_origen == "AX")
        {
            CX -= AX;
        }
        if (registro_origen == "BX")
        {
            CX -= BX;
        }
        if (registro_origen == "CX")
        {
            CX -= CX;
        }
        if (registro_origen == "DX")
        {
            CX -= DX;
        }
        if (registro_origen == "EX")
        {
            CX -= EX;
        }
        if (registro_origen == "FX")
        {
            CX -= FX;
        }
        if (registro_origen == "GX")
        {
            CX -= GX;
        }
        if (registro_origen == "HX")
        {
            CX -= HX;
        }
        if (registro_origen == "BASE")
        {
            CX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            CX -= LIMITE;
        }
    }
    if (registro_destino == "DX")
    {
        if (registro_origen == "PC")
        {
            DX -= PC;
        }
        if (registro_origen == "AX")
        {
            DX -= AX;
        }
        if (registro_origen == "BX")
        {
            DX -= BX;
        }
        if (registro_origen == "CX")
        {
            DX -= CX;
        }
        if (registro_origen == "DX")
        {
            DX -= DX;
        }
        if (registro_origen == "EX")
        {
            DX -= EX;
        }
        if (registro_origen == "FX")
        {
            DX -= FX;
        }
        if (registro_origen == "GX")
        {
            DX -= GX;
        }
        if (registro_origen == "HX")
        {
            DX -= HX;
        }
        if (registro_origen == "BASE")
        {
            DX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            DX -= LIMITE;
        }
    }
    if (registro_destino == "EX")
    {
        if (registro_origen == "PC")
        {
            EX -= PC;
        }
        if (registro_origen == "AX")
        {
            EX -= AX;
        }
        if (registro_origen == "BX")
        {
            EX -= BX;
        }
        if (registro_origen == "CX")
        {
            EX -= CX;
        }
        if (registro_origen == "DX")
        {
            EX -= DX;
        }
        if (registro_origen == "EX")
        {
            EX -= EX;
        }
        if (registro_origen == "FX")
        {
            EX -= FX;
        }
        if (registro_origen == "GX")
        {
            EX -= GX;
        }
        if (registro_origen == "HX")
        {
            EX -= HX;
        }
        if (registro_origen == "BASE")
        {
            EX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            EX -= LIMITE;
        }
    }
    if (registro_destino == "FX")
    {
        if (registro_origen == "PC")
        {
            FX -= PC;
        }
        if (registro_origen == "AX")
        {
            FX -= AX;
        }
        if (registro_origen == "BX")
        {
            FX -= BX;
        }
        if (registro_origen == "CX")
        {
            FX -= CX;
        }
        if (registro_origen == "DX")
        {
            FX -= DX;
        }
        if (registro_origen == "EX")
        {
            FX -= EX;
        }
        if (registro_origen == "FX")
        {
            FX -= FX;
        }
        if (registro_origen == "GX")
        {
            FX -= GX;
        }
        if (registro_origen == "HX")
        {
            FX -= HX;
        }
        if (registro_origen == "BASE")
        {
            FX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            FX -= LIMITE;
        }
    }
    if (registro_destino == "GX")
    {
        if (registro_origen == "PC")
        {
            GX -= PC;
        }
        if (registro_origen == "AX")
        {
            GX -= AX;
        }
        if (registro_origen == "BX")
        {
            GX -= BX;
        }
        if (registro_origen == "CX")
        {
            GX -= CX;
        }
        if (registro_origen == "DX")
        {
            GX -= DX;
        }
        if (registro_origen == "EX")
        {
            GX -= EX;
        }
        if (registro_origen == "FX")
        {
            GX -= FX;
        }
        if (registro_origen == "GX")
        {
            GX -= GX;
        }
        if (registro_origen == "HX")
        {
            GX -= HX;
        }
        if (registro_origen == "BASE")
        {
            GX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            GX -= LIMITE;
        }
    }
    if (registro_destino == "HX")
    {
        if (registro_origen == "PC")
        {
            HX -= PC;
        }
        if (registro_origen == "AX")
        {
            HX -= AX;
        }
        if (registro_origen == "BX")
        {
            HX -= BX;
        }
        if (registro_origen == "CX")
        {
            HX -= CX;
        }
        if (registro_origen == "DX")
        {
            HX -= DX;
        }
        if (registro_origen == "EX")
        {
            HX -= EX;
        }
        if (registro_origen == "FX")
        {
            HX -= FX;
        }
        if (registro_origen == "GX")
        {
            HX -= GX;
        }
        if (registro_origen == "HX")
        {
            HX -= HX;
        }
        if (registro_origen == "BASE")
        {
            HX -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            HX -= LIMITE;
        }
    }
    if (registro_destino == "BASE")
    {
        if (registro_origen == "PC")
        {
            BASE -= PC;
        }
        if (registro_origen == "AX")
        {
            BASE -= AX;
        }
        if (registro_origen == "BX")
        {
            BASE -= BX;
        }
        if (registro_origen == "CX")
        {
            BASE -= CX;
        }
        if (registro_origen == "DX")
        {
            BASE -= DX;
        }
        if (registro_origen == "EX")
        {
            BASE -= EX;
        }
        if (registro_origen == "FX")
        {
            BASE -= FX;
        }
        if (registro_origen == "GX")
        {
            BASE -= GX;
        }
        if (registro_origen == "HX")
        {
            BASE -= HX;
        }
        if (registro_origen == "BASE")
        {
            BASE -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            BASE -= LIMITE;
        }
    }
    if (registro_destino == "LIMITE")
    {
        if (registro_origen == "PC")
        {
            LIMITE -= PC;
        }
        if (registro_origen == "AX")
        {
            LIMITE -= AX;
        }
        if (registro_origen == "BX")
        {
            LIMITE -= BX;
        }
        if (registro_origen == "CX")
        {
            LIMITE -= CX;
        }
        if (registro_origen == "DX")
        {
            LIMITE -= DX;
        }
        if (registro_origen == "EX")
        {
            LIMITE -= EX;
        }
        if (registro_origen == "FX")
        {
            LIMITE -= FX;
        }
        if (registro_origen == "GX")
        {
            LIMITE -= GX;
        }
        if (registro_origen == "HX")
        {
            LIMITE -= HX;
        }
        if (registro_origen == "BASE")
        {
            LIMITE -= BASE;
        }
        if (registro_origen == "LIMITE")
        {
            LIMITE -= LIMITE;
        }
    }
    
    log_info(logger, "##PID: %d - Ejecutando: SUB - %s %s", tid, registro_destino, registro_origen);
}

void jnz(char *registro, char *instruccion)
{

    int valorASetear = atoi(instruccion);

    if (registro == "AX" && AX != 0)
    {   
        AX = valorASetear;
    }
    if (registro == "BX" && BX != 0)
    {   
        BX = valorASetear;
    }
    if (registro == "CX" && CX != 0)
    {   
        CX = valorASetear;
    }
    if (registro == "DX" && DX != 0)
    {   
        DX = valorASetear;
    }
    if (registro == "EX" && EX != 0)
    {   
        EX = valorASetear;
    }
    if (registro == "FX" && FX != 0)
    {   
        FX = valorASetear;
    }
    if (registro == "GX" && GX != 0)
    {   
        GX = valorASetear;
    }
    if (registro == "HX" && HX != 0)
    {   
        HX = valorASetear;
    }
    if (registro == "BASE" && BASE != 0)
    {   
        BASE = valorASetear;
    }
    if (registro == "LIMITE" && LIMITE != 0)
    {   
        LIMITE = valorASetear;
    }
    if (registro == "PC" && PC != 0)
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

    if (registro == "AX")
    {   
        valor_a_guardar = AX;
    }
    if (registro == "BX")
    {   
        valor_a_guardar = BX;
    }
    if (registro == "CX")
    {   
        valor_a_guardar = CX;
    }
    if (registro == "DX")
    {   
        valor_a_guardar = DX;
    }
    if (registro == "EX")
    {   
        valor_a_guardar = EX;
    }
    if (registro == "FX")
    {   
        valor_a_guardar = FX;
    }
    if (registro == "GX")
    {   
        valor_a_guardar = GX;
    }
    if (registro == "HX")
    {   
        valor_a_guardar = HX;
    }
    if (registro == "BASE")
    {   
        valor_a_guardar = BASE;
    }
    if (registro == "LIMITE")
    {   
        valor_a_guardar = LIMITE;
    }
    if (registro == "PC")
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