#ifndef __datetime__
#define __datetime__

#include <stdio.h>
#include <string.h>

typedef struct {

	int year,month,day,hour,min,seg;
	char cyear[4],cmonth[2],cday[2],chour[2],cmin[2],cseg[2];

} datetime_t;

int datetime_create(datetime_t *self);
int datetime_setdatetime (datetime_t *self, char* datetime);
int datetime_setyear(datetime_t *self, int year);
int datetime_setmonth(datetime_t *self, int month);
int datetime_setday(datetime_t *self, int day);
int datetime_sethour(datetime_t *self, int hour);
int datetime_setmin(datetime_t *self, int minute);
int datetime_setsec(datetime_t *self, int second);
int datetime_getsecond (datetime_t *self, int* second);
int datetime_getdatetimeformat1 (datetime_t *self, char* datetime);
int datetime_getdatetimeformat2 (datetime_t *self, char* datetime);
int datetime_minuteincrease (datetime_t *self);
int datetime_destroy(datetime_t *self);

#endif