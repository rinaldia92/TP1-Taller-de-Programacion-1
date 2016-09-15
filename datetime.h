#ifndef __datetime__
#define __datetime__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int year,month,day,hour,min,seg;
}datetime_t;

//Inicializa la estructura
int datetime_create(datetime_t *self);
//Setea fecha y hora
int datetime_setdatetime(datetime_t *self, char* datetime);
//Devuelve el valor de los segundos
int datetime_getsecond(datetime_t *self, int *second);
//Devuelve la fecha y hora
int datetime_getdatetime(datetime_t *self, char* datetime,size_t length);
//Devuelve la fecha
int datetime_getdate(datetime_t *self, char* date,size_t length);
//Devuelve el dia
int datetime_getday(datetime_t *self, int *day);
//Incrementa un minuto
int datetime_minuteincrease(datetime_t *self);
//Incrementa una hora
int datetime_hourincrease(datetime_t *self);
//Incrementa un dia
int datetime_dayincrease(datetime_t *self);
//Incrementa un mes
int datetime_monthincrease(datetime_t *self);
//Incrementa un anio
int datetime_yearincrease(datetime_t *self);
//Destruye la estructura
int datetime_destroy(datetime_t *self);

#endif
