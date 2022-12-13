#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void *funcion_hilo(void *elemento_)
{
        printf("Vengo desde un hilo\n");
        sleep(1);
        printf("Aca termine\n");
        int *elemento = elemento_;
        (*elemento) = (*elemento)+1;
        printf("elemento vale esto: %i \n", (*elemento));
        
        
        return elemento;
}

int main()
{
        pthread_t hilo1, hilo2;
        int numero = 0;

        //el segundo parametro son configuracion, lo ignoro (?
        //el tercero es la funcion del hilo
        //el ultimo es el argumento que se le pasa a la funcion del hilo
        if (pthread_create(&hilo1, NULL, &funcion_hilo, &numero) != 0) 
                return -1;
        
        if (pthread_create(&hilo2, NULL, &funcion_hilo, &numero) != 0)
                return -1;
        //es un "wait" pero para hilos
        //el segundo parametro es lo que devolveria el hilo (en mi caso nada, es void)
        void *numero_recibe;
        void *otro_numero_recibe;
        if (pthread_join(hilo1, &numero_recibe) != 0)
                return -1;

        printf("recibi esto del hilo1 %i \n", *(int *)(numero_recibe));

        if (pthread_join(hilo2, &otro_numero_recibe) != 0)
                return -1;

        printf("yo recibi esto del hilo2 %i \n", *(int *)(otro_numero_recibe));
        return 0;
}