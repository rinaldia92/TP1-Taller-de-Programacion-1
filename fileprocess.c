#include "fileprocess.h"

#define VALUELENGTH 7

int fileprocess_create(fileprocess_t *self, 	char* file){
	self->arch = fopen(file, "rb");
	self->endfile = false;
	if (self->arch)
		return 0;
	else
		return 1;
}

int fileprocess_getvalues(fileprocess_t *self, char* elem, int cant){
	int i;
	short value,endianvalue;
	float prevvalue,currentvalue;
	char cvalue[VALUELENGTH];
	bool lasttemp;

	prevvalue = 0.0;
	currentvalue = 0.0;
	lasttemp = false;

	strncat(elem," ",1);

	i = 0;

	while (!lasttemp && fread(&value,sizeof(short),1,self->arch)>0){
		endianvalue = htons(value);
		if (endianvalue > 0x02ff){
			currentvalue = prevvalue;
		} else {
			currentvalue = -17.0 + 0.1*endianvalue;
			prevvalue = currentvalue;
		}

		snprintf(cvalue,sizeof(cvalue), "%.1f", currentvalue);
		strncat(elem,cvalue,sizeof(cvalue));

		if (i<cant-1){
			strncat(elem," ",1);
			i++;
		} else {
			strncat(elem,"\n",1);
			i++;
			lasttemp = true;
		}
	}

	if (i>0 && i<=cant-1){
			strncat(elem,"\n",1);
			self->endfile = true;
	}

	if (i == 0){
			self->endfile = true;
	}
	return i;
}

int fileprocess_destroy(fileprocess_t *self){
	fclose(self->arch);
	return 0;
}

bool fileprocess_isempty(fileprocess_t *self){
	return self->endfile;
}
