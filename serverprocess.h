#ifndef __serverprocess__
#define __serverprocess__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int i;
    int cant;
    float *buffer;
    float min;
    float max;
    float med;
    }serverprocess_t;

//Inicializa la estructura
int serverprocess_create(serverprocess_t *self);

//Parsea el array y convierte los valores a float para guardarlos en el vector
int serverprocess_setvalues(serverprocess_t *self,char *values);

//Devuelve la cantidad de elementos que se guardaron en el vector
int serverprocess_getcant(serverprocess_t *self,int *cant);

//Devuelve la informacion sobre max, min y mediana
int serverprocess_getmed(serverprocess_t *self, char *buffer,size_t size);

//Funcion auxiliar para comparar floats
int serverprocess_compare(const void *elem1, const void *elem2);

//Ordena al vector
int serverprocess_order(serverprocess_t *self);

//Destruye los elementos de la estructura
int serverprocess_destroy(serverprocess_t *self);

#endif
