#include <../include/mmu.h>

bool validar_direccion(int direccion)
{
    return direccion < LIMITE;
}

int obtener_direccion_fisica(int direccion_logica)
{
    return BASE + direccion_logica;
}