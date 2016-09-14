#ifndef __datetime__
#define __datetime__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int year,month,day,hour,min,seg;
	char cyear[5],cmonth[3],cday[3],chour[3],cmin[3],cseg[3];
}datetime_t;

int datetime_create(datetime_t *self);
int datetime_setdatetime(datetime_t *self, char* datetime);
int datetime_getsecond(datetime_t *self, int *second);
int datetime_getdatetime(datetime_t *self, char* datetime);
int datetime_getdate(datetime_t *self, char* date);
int datetime_getday(datetime_t *self, int *day);
int datetime_minuteincrease(datetime_t *self);
int datetime_destroy(datetime_t *self);

#endif
