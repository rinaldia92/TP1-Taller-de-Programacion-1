#include "datetime.h"

int datetime_create(datetime_t *self){
	self->year = 0;
	self->month = 0;
	self->day = 0;
	self->hour = 0;
	self->min = 0;
	self->seg = 0;

	return 0;
}

int datetime_setdatetime(datetime_t *self, char* datetime){
	sscanf(datetime,"%d.%d.%d-%d:%d:%d",&(self->year),&(self->month),
	&(self->day),&(self->hour),&(self->min),&(self->seg));

	snprintf(self->cyear,sizeof(self->cyear), "%04d", self->year);
	snprintf(self->cmonth,sizeof(self->cmonth), "%02d", self->month);
	snprintf(self->cday,sizeof(self->cday), "%02d", self->day);
	snprintf(self->chour,sizeof(self->chour), "%02d",self->hour);
	snprintf(self->cmin,sizeof(self->cmin), "%02d", self->min);
	snprintf(self->cseg,sizeof(self->cseg), "%02d", self->seg);

	return 0;
}

int datetime_getsecond(datetime_t *self, int *second){
	*second = self->seg;

	return 0;
}

int datetime_getday(datetime_t *self, int *day){
	*day = self->day;

	return 0;
}

int datetime_getdatetime(datetime_t *self, char* datetime){
	 strncat(datetime, self->cyear,4);
   strncat(datetime, ".",1);
   strncat(datetime, self->cmonth,2);
   strncat(datetime, ".",1);
   strncat(datetime, self->cday,2);
   strncat(datetime, "-",1);
   strncat(datetime, self->chour,2);
   strncat(datetime, ":",1);
   strncat(datetime, self->cmin,2);
   strncat(datetime, ":",1);
   strncat(datetime, "00",2);

     return 0;
}


int datetime_getdate(datetime_t *self, char* date){
	 strncat(date, self->cyear,4);
   strncat(date, ".",1);
   strncat(date, self->cmonth,2);
   strncat(date, ".",1);
   strncat(date, self->cday,2);

   return 0;
}

int datetime_minuteincrease(datetime_t *self){
	if (self->min == 59){
		self->min = 0;
		if (self->hour == 23){
			self->hour = 0;
			switch (self->month){
				case 2:
					if(self->day == 28){
						self->day = 1;
						self->month += 1;
					} else {
						self->day += 1;
					}
					break;
				case 4: case 6: case 9: case 11:
					if(self->day == 30){
						self->day = 1;
						self->month += 1;
					} else {
						self->day += 1;
					}
					break;
				default:
					if(self->day == 31){
						self->day = 1;
						if (self->month == 12){
							self->month = 1;
							self->year += 1;
						}else{
							self->month += 1;
						}
					} else {
						self->day += 1;
					}
					break;
			}
		}else{
            self->hour += 1;
		}
	} else {
		self->min += 1;
	}

	snprintf(self->cyear,sizeof(self->cyear), "%04d", self->year);
 	snprintf(self->cmonth,sizeof(self->cmonth), "%02d", self->month);
 	snprintf(self->cday,sizeof(self->cday), "%02d", self->day);
 	snprintf(self->chour,sizeof(self->chour), "%02d",self->hour);
 	snprintf(self->cmin,sizeof(self->cmin), "%02d", self->min);
 	snprintf(self->cseg,sizeof(self->cseg), "%02d", self->seg);

	return 0;
}

int datetime_destroy(datetime_t *self){
	return 0;
}
