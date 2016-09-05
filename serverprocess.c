#include "serverprocess.h"

int serverprocess_create (serverprocess_t *self){

		queue_create(&(self->queue),sizeof(float));
		//datetime_create(&(self->datetime));
		return 0;
}

int serverprocess_setID(serverprocess_t *self,char *buffer, size_t size){


	return 0;
}

int serverprocess_setvalues(serverprocess_t *self,char *buffer, size_t size){

	char datetimeaux[20];
	char* aux;
	float value;
	char cvalue[5];

	aux = "";

	//char *bufferaux = malloc (size);

	self->cantidadparcial = 0;
	sscanf(buffer,"%s %[^\n]",self->datetimeaux,buffer);

	while (strlen(buffer)>5){
         sscanf(buffer,"%s %[^\n]",cvalue,buffer);
         value = strtof(cvalue,&aux);
         queue_push(&(self->queue),&value);
         self->cantidadparcial++;

        }
        sscanf(buffer,"%s %[^\n]",cvalue,buffer);
        queue_push(&(self->queue),&value);
         //printf("%s\n",aux2);
         self->cantidadparcial++;

	//free(bufferaux);

	return 0;
}

int serverprocess_getcantpar (serverprocess_t *self,int *cant){

	*cant = self->cantidadparcial;

	return 0;
}

int serverprocess_getdatetime (serverprocess_t *self,char* buffer){

	strcat(buffer,self->datetimeaux); 

	return 0;
}


int serverprocess_destroy (serverprocess_t *self){

	queue_empty(&(self->queue));
	//datetime_destroy(self->datetime);

	return 0;
}		
