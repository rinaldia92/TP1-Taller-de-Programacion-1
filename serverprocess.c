#include "serverprocess.h"

#define INICANT 1000 //cantidad inicial del vector
#define VALUELENGTH 7

int serverprocess_create(serverprocess_t *self){
		self->i = 0;
		self->cant = INICANT;
		self->buffer = malloc((self->cant)*sizeof(float));
		(self->buffer)[0]=0;
		return 0;
}

//Guarda los valores en el vector y si es necesario lo agranda
int serverprocess_setvalues(serverprocess_t *self,char *values){
	float value;
	char cvalue[VALUELENGTH];
	int cant = 0;
	char *aux = "";

	while (strlen(values)> 6){
		sscanf(values,"%s %[^\n]",cvalue,values);
		value = strtof(cvalue,&aux);
		if(self->i == self->cant){
			self->cant = 2*self->cant;
			self->buffer = realloc(self->buffer,(self->cant)*sizeof(float));
		}
		(self->buffer)[self->i] = value;
		(self->i)++;
		cant++;
	}
	sscanf(values,"%s %[^\n]",cvalue,values);
	value = strtof(cvalue,&aux);
	cant++;

	if(self->i == self->cant){
		self->cant = 2*self->cant;
		self->buffer = realloc(self->buffer,(self->cant)*sizeof(float));
	}
	(self->buffer)[self->i] = value;

	(self->i)++;

	return cant;
}

int serverprocess_getcant(serverprocess_t *self,int *cant){
	*cant = self->i;

	return 0;
}

int serverprocess_getmed(serverprocess_t *self, char *buffer,size_t size){
		self->min = (self->buffer)[0];
		self->max = (self->buffer)[(self->i)-1];

		if ((self->i)%2 == 0)
			self->med = (self->buffer)[(self->i)/2 - 1];
		else
			self->med = (self->buffer)[(self->i)/2];

	snprintf(buffer,size, "Max=%.1f Min=%.1f Mediana=%.1f Muestras=%d",
	self->max,self->min,self->med,self->i);

	(self->buffer)[0]=0;
	self->i = 0;

	return 0;
}

int serverprocess_compare(const void *elem1, const void *elem2) {
        float *a, *b;
        a = (float *) elem1;
        b = (float *) elem2;

				if (*a > *b){
        	return 1;
				}else{
					if (*a < *b){
						return -1;
					} else{
						return 0;
					}
				}
}

int serverprocess_order(serverprocess_t *self){
	qsort(self->buffer, self->i, sizeof(float), &serverprocess_compare);
	return 0;
}

int serverprocess_destroy(serverprocess_t *self){
	free(self->buffer);
	return 0;
}
