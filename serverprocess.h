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


int serverprocess_create(serverprocess_t *self);
int serverprocess_setvalues(serverprocess_t *self,float value);
int serverprocess_getcant(serverprocess_t *self,int *cant);
int serverprocess_getmed(serverprocess_t *self, char *buffer);
int serverprocess_order(serverprocess_t *self);
int serverprocess_destroy(serverprocess_t *self);

#endif
