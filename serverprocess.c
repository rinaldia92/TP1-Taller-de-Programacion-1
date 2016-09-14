#include "serverprocess.h"

int serverprocess_create(serverprocess_t *self){
		self->i = 0;
		self->cant = 1000;
		self->buffer = malloc((self->cant)*sizeof(float));
		memset(self->buffer,0,self->cant);
		return 0;
}

int serverprocess_setvalues(serverprocess_t *self,float value){
	if(self->i == self->cant){
		self->cant = 2*self->cant;
		self->buffer = realloc(self->buffer,(self->cant)*sizeof(float));
	}
	(self->buffer)[self->i] = value;

	(self->i)++;

	return 0;
}

int serverprocess_getcant(serverprocess_t *self,int *cant){
	*cant = self->i;

	return 0;
}

int serverprocess_getmed(serverprocess_t *self, char *buffer){
	char aux[10];
	strncat(buffer," Max=",5);
	snprintf(aux,sizeof(aux), "%.1f", self->max);
	strncat(buffer,aux,5);
	strncat(buffer," Min=",5);
	snprintf(aux,sizeof(aux), "%.1f", self->min);
	strncat(buffer,aux,5);
	strncat(buffer," Mediana=",9);
	snprintf(aux,sizeof(aux), "%.1f", self->med);
	strncat(buffer,aux,5);
	strncat(buffer," Muestras=",10);
	snprintf(aux,sizeof(aux), "%d", self->i);
	strncat(buffer,aux,10);

	memset(self->buffer,0,self->cant);
	self->i = 0;

	return 0;
}

int serverprocess_order(serverprocess_t *self){
		int j,s,smin;
		float valuesaux;

		for (s=0; s<(self->i); s++){
		  smin=s;
		  for (j=s+1; j<(self->i); j++){
		    if ((self->buffer)[j]<(self->buffer)[smin])
		    	smin=j;
		  }
		  valuesaux = (self->buffer)[s];
			(self->buffer)[s] = (self->buffer)[smin];
		  (self->buffer)[smin] = valuesaux;
		}

		self->min = (self->buffer)[0];
		self->max = (self->buffer)[(self->i)-1];

		if ((self->i)%2 == 0)
			self->med = (self->buffer)[(self->i)/2 - 1];
		else
			self->med = (self->buffer)[(self->i)/2];

	return 0;
}

int serverprocess_destroy(serverprocess_t *self){
	free(self->buffer);
	return 0;
}
