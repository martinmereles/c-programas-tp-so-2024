#include <../include/instrucciones_cpu.h>

/*----------------------------------SET DE INSTRUCCIONES---------------------------------*/
void set(char *registro, char *valor){

    int valorASetear = atoi(valor);
    switch (deCharAEnum(registro))
    {
    case AX:
        reg->AX = valorASetear;
        break;
    case BX:
        reg->BX = valorASetear;
        break;
    case CX:
        reg->CX = valorASetear;
        break;
    case DX:
        reg->DX = valorASetear;
        break;
    case EX:
        reg->EX = valorASetear;
        break;
    case FX:
        reg->FX = valorASetear;
        break;
    case GX:
        reg->GX = valorASetear;
        break;
    case HX:
        reg->HX = valorASetear;
        break;
    case PC:
        reg->PC = valorASetear;
        break;
    case BASE:
        reg->BASE = valorASetear;
        break;
    case LIMITE:
        reg->LIMITE = valorASetear;
        break;
    default:
        break;
    }
    //log_info(logger, "##TID: %d - Ejecutando: SET - %s %s", contexto->pid, registro, valor);
}

void read_mem(){
    //TO DO
}

void write_mem(){
    //TO DO
}

void sum(char *registro_destino, char *registro_origen){

    switch (deCharAEnum(registro_destino)){
        case AX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->AX += reg->AX;
                    break;
                case BX:
                    reg->AX += reg->BX;
                    break;
                case CX:
                    reg->AX += reg->CX;
                    break;
                case DX:
                    reg->AX += reg->DX;
                    break;
                case EX:
                    reg->AX += reg->EX;
                    break;
                case FX:
                    reg->AX += reg->FX;
                    break;
                case GX:
                    reg->AX += reg->GX;
                    break;
                case HX:
                    reg->AX += reg->HX;
                    break;
                case PC:
                    reg->AX += reg->PC;
                    break;
                case BASE:
                    reg->AX += reg->BASE;
                    break;
                case LIMITE:
                    reg->AX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case BX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->BX += reg->AX;
                    break;
                case BX:
                    reg->BX += reg->BX;
                    break;
                case CX:
                    reg->BX += reg->CX;
                    break;
                case DX:
                    reg->BX += reg->DX;
                    break;
                case EX:
                    reg->BX += reg->EX;
                    break;
                case FX:
                    reg->BX += reg->FX;
                    break;
                case GX:
                    reg->BX += reg->GX;
                    break;
                case HX:
                    reg->BX += reg->HX;
                    break;
                case PC:
                    reg->BX += reg->PC;
                    break;
                case BASE:
                    reg->BX += reg->BASE;
                    break;
                case LIMITE:
                    reg->BX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case CX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->CX += reg->AX;
                    break;
                case BX:
                    reg->CX += reg->BX;
                    break;
                case CX:
                    reg->CX += reg->CX;
                    break;
                case DX:
                    reg->CX += reg->DX;
                    break;
                case EX:
                    reg->CX += reg->EX;
                    break;
                case FX:
                    reg->CX += reg->FX;
                    break;
                case GX:
                    reg->CX += reg->GX;
                    break;
                case HX:
                    reg->CX += reg->HX;
                    break;
                case PC:
                    reg->CX += reg->PC;
                    break;
                case BASE:
                    reg->CX += reg->BASE;
                    break;
                case LIMITE:
                    reg->CX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case DX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->DX += reg->AX;
                    break;
                case BX:
                    reg->DX += reg->BX;
                    break;
                case CX:
                    reg->DX += reg->CX;
                    break;
                case DX:
                    reg->DX += reg->DX;
                    break;
                case EX:
                    reg->DX += reg->EX;
                    break;
                case FX:
                    reg->DX += reg->FX;
                    break;
                case GX:
                    reg->DX += reg->GX;
                    break;
                case HX:
                    reg->DX += reg->HX;
                    break;
                case PC:
                    reg->DX += reg->PC;
                    break;
                case BASE:
                    reg->DX += reg->BASE;
                    break;
                case LIMITE:
                    reg->DX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case EX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->EX += reg->AX;
                    break;
                case BX:
                    reg->EX += reg->BX;
                    break;
                case CX:
                    reg->EX += reg->CX;
                    break;
                case DX:
                    reg->EX += reg->DX;
                    break;
                case EX:
                    reg->EX += reg->EX;
                    break;
                case FX:
                    reg->EX += reg->FX;
                    break;
                case GX:
                    reg->EX += reg->GX;
                    break;
                case HX:
                    reg->EX += reg->HX;
                    break;
                case PC:
                    reg->EX += reg->PC;
                    break;
                case BASE:
                    reg->EX += reg->BASE;
                    break;
                case LIMITE:
                    reg->EX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case FX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->FX += reg->AX;
                    break;
                case BX:
                    reg->FX += reg->BX;
                    break;
                case CX:
                    reg->FX += reg->CX;
                    break;
                case DX:
                    reg->FX += reg->DX;
                    break;
                case EX:
                    reg->FX += reg->EX;
                    break;
                case FX:
                    reg->FX += reg->FX;
                    break;
                case GX:
                    reg->FX += reg->GX;
                    break;
                case HX:
                    reg->FX += reg->HX;
                    break;
                case PC:
                    reg->FX += reg->PC;
                    break;
                case BASE:
                    reg->FX += reg->BASE;
                    break;
                case LIMITE:
                    reg->FX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case GX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->GX += reg->AX;
                    break;
                case BX:
                    reg->GX += reg->BX;
                    break;
                case CX:
                    reg->GX += reg->CX;
                    break;
                case DX:
                    reg->GX += reg->DX;
                    break;
                case EX:
                    reg->GX += reg->EX;
                    break;
                case FX:
                    reg->GX += reg->FX;
                    break;
                case GX:
                    reg->GX += reg->GX;
                    break;
                case HX:
                    reg->GX += reg->HX;
                    break;
                case PC:
                    reg->GX += reg->PC;
                    break;
                case BASE:
                    reg->GX += reg->BASE;
                    break;
                case LIMITE:
                    reg->GX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case HX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->HX += reg->AX;
                    break;
                case BX:
                    reg->HX += reg->BX;
                    break;
                case CX:
                    reg->HX += reg->CX;
                    break;
                case DX:
                    reg->HX += reg->DX;
                    break;
                case EX:
                    reg->HX += reg->EX;
                    break;
                case FX:
                    reg->HX += reg->FX;
                    break;
                case GX:
                    reg->HX += reg->GX;
                    break;
                case HX:
                    reg->HX += reg->HX;
                    break;
                case PC:
                    reg->HX += reg->PC;
                    break;
                case BASE:
                    reg->HX += reg->BASE;
                    break;
                case LIMITE:
                    reg->HX += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case PC:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->PC += reg->AX;
                    break;
                case BX:
                    reg->PC += reg->BX;
                    break;
                case CX:
                    reg->PC += reg->CX;
                    break;
                case DX:
                    reg->PC += reg->DX;
                    break;
                case EX:
                    reg->PC += reg->EX;
                    break;
                case FX:
                    reg->PC += reg->FX;
                    break;
                case GX:
                    reg->PC += reg->GX;
                    break;
                case HX:
                    reg->PC += reg->HX;
                    break;
                case PC:
                    reg->PC += reg->PC;
                    break;
                case BASE:
                    reg->PC += reg->BASE;
                    break;
                case LIMITE:
                    reg->PC += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case BASE:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->BASE += reg->AX;
                    break;
                case BX:
                    reg->BASE += reg->BX;
                    break;
                case CX:
                    reg->BASE += reg->CX;
                    break;
                case DX:
                    reg->BASE += reg->DX;
                    break;
                case EX:
                    reg->BASE += reg->EX;
                    break;
                case FX:
                    reg->BASE += reg->FX;
                    break;
                case GX:
                    reg->BASE += reg->GX;
                    break;
                case HX:
                    reg->BASE += reg->HX;
                    break;
                case PC:
                    reg->BASE += reg->PC;
                    break;
                case BASE:
                    reg->BASE += reg->BASE;
                    break;
                case LIMITE:
                    reg->BASE += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case LIMITE:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->LIMITE += reg->AX;
                    break;
                case BX:
                    reg->LIMITE += reg->BX;
                    break;
                case CX:
                    reg->LIMITE += reg->CX;
                    break;
                case DX:
                    reg->LIMITE += reg->DX;
                    break;
                case EX:
                    reg->LIMITE += reg->EX;
                    break;
                case FX:
                    reg->LIMITE += reg->FX;
                    break;
                case GX:
                    reg->LIMITE += reg->GX;
                    break;
                case HX:
                    reg->LIMITE += reg->HX;
                    break;
                case PC:
                    reg->LIMITE += reg->PC;
                    break;
                case BASE:
                    reg->LIMITE += reg->BASE;
                    break;
                case LIMITE:
                    reg->LIMITE += reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    //log_info(logger, "##tID: %d - Ejecutando: SUM - %s %s", contexto->pid, registro_destino, registro_origen);
}

void sub(char *registro_destino, char *registro_origen){

    switch (deCharAEnum(registro_destino)){
        case AX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->AX -= reg->AX;
                    break;
                case BX:
                    reg->AX -= reg->BX;
                    break;
                case CX:
                    reg->AX -= reg->CX;
                    break;
                case DX:
                    reg->AX -= reg->DX;
                    break;
                case EX:
                    reg->AX -= reg->EX;
                    break;
                case FX:
                    reg->AX -= reg->FX;
                    break;
                case GX:
                    reg->AX -= reg->GX;
                    break;
                case HX:
                    reg->AX -= reg->HX;
                    break;
                case PC:
                    reg->AX -= reg->PC;
                    break;
                case BASE:
                    reg->AX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->AX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case BX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->BX -= reg->AX;
                    break;
                case BX:
                    reg->BX -= reg->BX;
                    break;
                case CX:
                    reg->BX -= reg->CX;
                    break;
                case DX:
                    reg->BX -= reg->DX;
                    break;
                case EX:
                    reg->BX -= reg->EX;
                    break;
                case FX:
                    reg->BX -= reg->FX;
                    break;
                case GX:
                    reg->BX -= reg->GX;
                    break;
                case HX:
                    reg->BX -= reg->HX;
                    break;
                case PC:
                    reg->BX -= reg->PC;
                    break;
                case BASE:
                    reg->BX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->BX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case CX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->CX -= reg->AX;
                    break;
                case BX:
                    reg->CX -= reg->BX;
                    break;
                case CX:
                    reg->CX -= reg->CX;
                    break;
                case DX:
                    reg->CX -= reg->DX;
                    break;
                case EX:
                    reg->CX -= reg->EX;
                    break;
                case FX:
                    reg->CX -= reg->FX;
                    break;
                case GX:
                    reg->CX -= reg->GX;
                    break;
                case HX:
                    reg->CX -= reg->HX;
                    break;
                case PC:
                    reg->CX -= reg->PC;
                    break;
                case BASE:
                    reg->CX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->CX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case DX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->DX -= reg->AX;
                    break;
                case BX:
                    reg->DX -= reg->BX;
                    break;
                case CX:
                    reg->DX -= reg->CX;
                    break;
                case DX:
                    reg->DX -= reg->DX;
                    break;
                case EX:
                    reg->DX -= reg->EX;
                    break;
                case FX:
                    reg->DX -= reg->FX;
                    break;
                case GX:
                    reg->DX -= reg->GX;
                    break;
                case HX:
                    reg->DX -= reg->HX;
                    break;
                case PC:
                    reg->DX -= reg->PC;
                    break;
                case BASE:
                    reg->DX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->DX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case EX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->EX -= reg->AX;
                    break;
                case BX:
                    reg->EX -= reg->BX;
                    break;
                case CX:
                    reg->EX -= reg->CX;
                    break;
                case DX:
                    reg->EX -= reg->DX;
                    break;
                case EX:
                    reg->EX -= reg->EX;
                    break;
                case FX:
                    reg->EX -= reg->FX;
                    break;
                case GX:
                    reg->EX -= reg->GX;
                    break;
                case HX:
                    reg->EX -= reg->HX;
                    break;
                case PC:
                    reg->EX -= reg->PC;
                    break;
                case BASE:
                    reg->EX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->EX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case FX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->FX -= reg->AX;
                    break;
                case BX:
                    reg->FX -= reg->BX;
                    break;
                case CX:
                    reg->FX -= reg->CX;
                    break;
                case DX:
                    reg->FX -= reg->DX;
                    break;
                case EX:
                    reg->FX -= reg->EX;
                    break;
                case FX:
                    reg->FX -= reg->FX;
                    break;
                case GX:
                    reg->FX -= reg->GX;
                    break;
                case HX:
                    reg->FX -= reg->HX;
                    break;
                case PC:
                    reg->FX -= reg->PC;
                    break;
                case BASE:
                    reg->FX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->FX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case GX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->GX -= reg->AX;
                    break;
                case BX:
                    reg->GX -= reg->BX;
                    break;
                case CX:
                    reg->GX -= reg->CX;
                    break;
                case DX:
                    reg->GX -= reg->DX;
                    break;
                case EX:
                    reg->GX -= reg->EX;
                    break;
                case FX:
                    reg->GX -= reg->FX;
                    break;
                case GX:
                    reg->GX -= reg->GX;
                    break;
                case HX:
                    reg->GX -= reg->HX;
                    break;
                case PC:
                    reg->GX -= reg->PC;
                    break;
                case BASE:
                    reg->GX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->GX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case HX:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->HX -= reg->AX;
                    break;
                case BX:
                    reg->HX -= reg->BX;
                    break;
                case CX:
                    reg->HX -= reg->CX;
                    break;
                case DX:
                    reg->HX -= reg->DX;
                    break;
                case EX:
                    reg->HX -= reg->EX;
                    break;
                case FX:
                    reg->HX -= reg->FX;
                    break;
                case GX:
                    reg->HX -= reg->GX;
                    break;
                case HX:
                    reg->HX -= reg->HX;
                    break;
                case PC:
                    reg->HX -= reg->PC;
                    break;
                case BASE:
                    reg->HX -= reg->BASE;
                    break;
                case LIMITE:
                    reg->HX -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case PC:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->PC -= reg->AX;
                    break;
                case BX:
                    reg->PC -= reg->BX;
                    break;
                case CX:
                    reg->PC -= reg->CX;
                    break;
                case DX:
                    reg->PC -= reg->DX;
                    break;
                case EX:
                    reg->PC -= reg->EX;
                    break;
                case FX:
                    reg->PC -= reg->FX;
                    break;
                case GX:
                    reg->PC -= reg->GX;
                    break;
                case HX:
                    reg->PC -= reg->HX;
                    break;
                case PC:
                    reg->PC -= reg->PC;
                    break;
                case BASE:
                    reg->PC -= reg->BASE;
                    break;
                case LIMITE:
                    reg->PC -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case BASE:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->BASE -= reg->AX;
                    break;
                case BX:
                    reg->BASE -= reg->BX;
                    break;
                case CX:
                    reg->BASE -= reg->CX;
                    break;
                case DX:
                    reg->BASE -= reg->DX;
                    break;
                case EX:
                    reg->BASE -= reg->EX;
                    break;
                case FX:
                    reg->BASE -= reg->FX;
                    break;
                case GX:
                    reg->BASE -= reg->GX;
                    break;
                case HX:
                    reg->BASE -= reg->HX;
                    break;
                case PC:
                    reg->BASE -= reg->PC;
                    break;
                case BASE:
                    reg->BASE -= reg->BASE;
                    break;
                case LIMITE:
                    reg->BASE -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        case LIMITE:
            switch (deCharAEnum(registro_origen)){
                case AX:
                    reg->LIMITE -= reg->AX;
                    break;
                case BX:
                    reg->LIMITE -= reg->BX;
                    break;
                case CX:
                    reg->LIMITE -= reg->CX;
                    break;
                case DX:
                    reg->LIMITE -= reg->DX;
                    break;
                case EX:
                    reg->LIMITE -= reg->EX;
                    break;
                case FX:
                    reg->LIMITE -= reg->FX;
                    break;
                case GX:
                    reg->LIMITE -= reg->GX;
                    break;
                case HX:
                    reg->LIMITE -= reg->HX;
                    break;
                case PC:
                    reg->LIMITE -= reg->PC;
                    break;
                case BASE:
                    reg->LIMITE -= reg->BASE;
                    break;
                case LIMITE:
                    reg->LIMITE -= reg->LIMITE;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    //log_info(logger, "##PID: %d - Ejecutando: SUB - %s %s", contexto->pid,registro_destino, registro_origen);
}

void jnz(char *registro, char *instruccion){

    int valorASetear = atoi(instruccion);
    switch (deCharAEnum(registro)){
        case AX:
            if (reg->AX != 0)
                reg->PC = valorASetear;
            break;
        case BX:
            if (reg->BX != 0)
                reg->PC = valorASetear;
            break;
        case CX:
            if (reg->CX != 0)
                reg->PC = valorASetear;
            break;
        case DX:
            if (reg->DX != 0)
                reg->PC = valorASetear;
            break;
        case EX:
            if (reg->EX != 0)
                reg->PC = valorASetear;
            break;
        case FX:
            if (reg->FX != 0)
                reg->PC = valorASetear;
            break;
        case GX:
            if (reg->GX != 0)
                reg->PC = valorASetear;
            break;
        case HX:
            if (reg->HX != 0)
                reg->PC = valorASetear;
            break;
        case PC:
            if (reg->PC != 0)
                reg->PC = valorASetear;
            break;
        case BASE:
            if (reg->BASE != 0)
                reg->PC = valorASetear;
            break;
        case LIMITE:
            if (reg->LIMITE != 0)
                reg->PC = valorASetear;
            break;
        default:
            break;
    }
    log_info(logger, "##TID: %d - Ejecutando: JNZ - %s %s", contexto->pid, registro, instruccion);
}

void log(){
    //TO DO
}