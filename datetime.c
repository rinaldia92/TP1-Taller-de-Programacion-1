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

int datetime_getdatetime(datetime_t *self, char* datetime,size_t length){
	 snprintf(datetime,length, "%04d.%02d.%02d-%02d:%02d:00",
	 self->year,self->month,self->day,self->hour,self->min);

     return 0;
}


int datetime_getdate(datetime_t *self, char* date,size_t length){
	 snprintf(date,length, "%04d.%02d.%02d",self->year,self->month,self->day);

   return 0;
}

int datetime_yearincrease(datetime_t *self){
    self->year+=1;
    return 0;
}

int datetime_monthincrease(datetime_t *self){
    if (self->month == 12){
        self->month = 1;
        datetime_yearincrease(self);
    }else{
        self->month += 1;
    }
    return 0;
}

int datetime_dayincrease(datetime_t *self){
    switch (self->month){
        case 2:
            if (self->day == 28){
                self->day = 1;
                datetime_monthincrease(self);
            } else {
                self->day += 1;
            }
            break;
        case 4: case 6: case 9: case 11:
            if (self->day == 30){
                self->day = 1;
                datetime_monthincrease(self);
            } else {
                self->day += 1;
            }
            break;
        default:
            if (self->day == 31){
                self->day = 1;
                datetime_monthincrease(self);
            } else {
                self->day += 1;
            }
            break;
    }
    return 0;
}


int datetime_hourincrease(datetime_t *self){
    if (self->hour == 23){
        self->hour = 0;
        datetime_dayincrease(self);
    } else {
        self->hour++;
    }
    return 0;
}

int datetime_minuteincrease(datetime_t *self){
	if (self->min == 59){
        self->min = 0;
        datetime_hourincrease(self);
	} else {
		self->min += 1;
	}
	return 0;
}

int datetime_destroy(datetime_t *self){
	return 0;
}
