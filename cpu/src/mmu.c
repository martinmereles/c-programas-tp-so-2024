#include <../include/mmu.h>

void validar_direccion(int direccion)
{
    if(direccion < LIMITE){
        direccion_fisica = obtener_direccion_fisica(direccion);
    }else{
        //Segmentation fault
        //Mensaje a memoria para actualizar contexto
        crear_paquete_contexto();
        
        //Mensaje a Kernel con tid con motivo segmentation fault
        char* mensaje = string_new();
        string_append(&mensaje,"SEGMENTATION_FAULT ");
        string_append(&mensaje, tid);
        enviar_mensaje(mensaje ,socket_kernel_dispatch);
        sem_wait(&sem_execute);
    }
}

int obtener_direccion_fisica(int direccion_logica)
{
    return BASE + direccion_logica;
}