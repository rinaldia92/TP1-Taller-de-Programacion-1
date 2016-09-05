#ifndef __serverprocess__
#define __serverprocess__



#include "queue.h"
//#include "datetime.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <datetime.h>

typedef struct {
    //datetime_t datetime;
    int cantidadparcial;
    int cantidadtotal;
    char datetimeaux[20];
    queue_t queue;
    char *id;
    }serverprocess_t;


int serverprocess_create (serverprocess_t *self);

int serverprocess_setID(serverprocess_t *self,char *buffer, size_t size);

int serverprocess_setvalues(serverprocess_t *self,char *buffer, size_t size);

int serverprocess_getcantpar (serverprocess_t *self,int *cant);

int serverprocess_destroy (serverprocess_t *self);		

#endif