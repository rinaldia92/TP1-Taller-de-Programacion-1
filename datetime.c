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

int datetime_setdatetime (datetime_t *self, char* datetime){

	sscanf(datetime,"%[^.].%[^.].%[^-]-%[^:]:%[^:]:%s",self->cyear,self->cmonth,self->cday,self->chour,self->cmin,self->cseg);

	self->year = atoi(self->cyear);  
	self->month  = atoi(self->cmonth);
	self->day  = atoi(self->cday);
	self->hour  = atoi(self->chour);
	self->min  = atoi(self->cmin);
	self->seg  = atoi(self->cseg); 

	return 0;

}

int datetime_setyear(datetime_t *self, int year){

	self->year = year;

	return 0;

}

int datetime_setmonth(datetime_t *self, int month){

	self->month = month;

	return 0;

}

int datetime_setday(datetime_t *self, int day){

	self->day = day;

	return 0;

}

int datetime_sethour(datetime_t *self, int hour){

	self->hour = hour;

	return 0;

}

int datetime_setmin(datetime_t *self, int minute){

	self->min = minute;

	return 0;

}

int datetime_setsec(datetime_t *self, int second){

	self->seg = second;

	return 0;

}

int datetime_getsecond (datetime_t *self, int* second){

	second = self->seg;

	return 0;

}

int datetime_getdatetimeformat1 (datetime_t *self, char* datetime){

	 strcpy(datetime, self->cyear);
     strcat(datetime, ".");
     strcat(datetime, self->cmonth);
     strcat(datetime, ".");
     strcat(datetime, self->cday);
     strcat(datetime, "-");
     strcat(datetime, self->chour);
     strcat(datetime, ":");
     strcat(datetime, self->cmin);
     strcat(datetime, ":");
     strcat(datetime, "00");

     return 0;

}

int datetime_getdatetimeformat2 (datetime_t *self, char* datetime){

	 strcpy(datetime, self->cyear);
     strcat(datetime, "-");
     strcat(datetime, self->cmonth);
     strcat(datetime, "-");
     strcat(datetime, self->cday);
     strcat(datetime, "-");
     strcat(datetime, self->chour);
     strcat(datetime, ":");
     strcat(datetime, self->cmin);
     strcat(datetime, ":");
     strcat(datetime, "00");

     return 0;

}

int datetime_minuteincrease (datetime_t *self){
	
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

	sprintf(self->cyear, "%04d", self->year);
   	sprintf(self->cmonth, "%02d", self->month);
   	sprintf(self->cday, "%02d", self->day);
   	sprintf(self->chour, "%02d",self->hour);
   	sprintf(self->cmin, "%02d", self->min);
   	sprintf(self->cseg, "%02d", self->seg);

	return 0;
}

int datetime_destroy(datetime_t *self){

	return 0;	
}



