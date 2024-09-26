#include <../include/auxiliares.h>

int deCharAEnum(char *registro)
{
    if (strcmp(registro, "AX") == 0)
    {
        return AX;
    }
    if (strcmp(registro, "BX") == 0)
    {
        return BX;
    }
    if (strcmp(registro, "CX") == 0)
    {
        return CX;
    }
    if (strcmp(registro, "DX") == 0)
    {
        return DX;
    }
    if (strcmp(registro, "EX") == 0)
    {
        return EX;
    }
    if (strcmp(registro, "FX") == 0)
    {
        return FX;
    }
    if (strcmp(registro, "GX") == 0)
    {
        return GX;
    }
    if (strcmp(registro, "HX") == 0)
    {
        return HX;
    }
    if (strcmp(registro, "PC") == 0)
    {
        return PC;
    }
    if (strcmp(registro, "BASE") == 0)
    {
        return BASE;
    }
    if (strcmp(registro, "LIMITE") == 0)
    {
        return LIMITE;
    }
}