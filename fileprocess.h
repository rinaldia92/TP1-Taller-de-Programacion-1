#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <arpa/inet.h>


typedef struct {
    FILE* arch;
    bool endfile;
    }fileprocess_t;

//Inicializa la estructura y abre el archivo
int fileprocess_create(fileprocess_t *self, char* file);

//Devuelve si el archivo esta vacio o no
bool fileprocess_isempty(fileprocess_t *self);

//Devuelve un buffer cargado con cierta cantidad de temperaturas
int fileprocess_getvalues(fileprocess_t *self, char* elem, int cant);

//Cierra el archivo
int fileprocess_destroy(fileprocess_t *self);
