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


int fileprocess_create(fileprocess_t *self, char* file);
bool fileprocess_isempty(fileprocess_t *self);
int fileprocess_getvalues(fileprocess_t *self, char* elem, int cant);
int fileprocess_destroy(fileprocess_t *self);
