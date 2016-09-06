#include "serverprocess.h"

int serverprocess_create (serverprocess_t *self){

		queue_create(&(self->queuetemp),sizeof(float));
		queue_create(&(self->queuedatetime),20*sizeof(char));
		queue_create(&(self->queuecant),sizeof(int));
		datetime_create(&(self->datetime));
		return 0;
}

int serverprocess_setvalues(serverprocess_t *self,char *buffer, size_t size){

	char datetimeaux[20];
	char* aux;
	float value;
	char cvalue[5];

	aux = "";

	self->cantidadparcial = 0;
	sscanf(buffer,"%s %[^\n]",self->datetimeaux,buffer);

	queue_push(&(self->queuedatetime),self->datetimeaux);

	while (strlen(buffer)>5){
         sscanf(buffer,"%s %[^\n]",cvalue,buffer);
         value = strtof(cvalue,&aux);
         queue_push(&(self->queuetemp),&value);
         self->cantidadparcial++;
         

    }
    sscanf(buffer,"%s %[^\n]",cvalue,buffer);
    queue_push(&(self->queuetemp),&value);
    self->cantidadparcial++;
    queue_push(&(self->queuecant),&(self->cantidadparcial));


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

int serverprocess_all(serverprocess_t *self){

	int s,j,smin;
	char buffer[20];
	char bufferdate[10];
	int lastday = 0;
	int day;
	int cant = 0;
	int cantaux;

	float *values;
	float valuesaux,max,min,mediana;

	queue_t datesaux;
	queue_t ccantaux;

	queue_create(&datesaux,10*sizeof(char));
	queue_create(&ccantaux,sizeof(int));

	memset(bufferdate,0,10);

	s = queue_pop(&(self->queuedatetime),buffer);
	s = queue_pop(&(self->queuedatetime),buffer);
	s = datetime_setdatetime(&(self->datetime),buffer);
	s = datetime_getday(&(self->datetime),&day);
	lastday = day;
	s = queue_pop(&(self->queuecant),&cantaux);
	s = queue_pop(&(self->queuecant),&cantaux);
	cant += cantaux;
	s = datetime_getdate(&(self->datetime),bufferdate);

	memset(buffer,0,20);
	

	while (!queue_isempty(self->queuedatetime)){

		s = queue_pop(&(self->queuedatetime),buffer);
		
		s = datetime_setdatetime(&(self->datetime),buffer);
		s = datetime_getday(&(self->datetime),&day);
		memset(buffer,0,20);
		if (day != lastday){
			lastday = day;
			
			s = queue_push(&datesaux,bufferdate);
			s = queue_push(&ccantaux,&cant);
			memset(bufferdate,0,10);
			s = datetime_getdate(&(self->datetime),bufferdate);
			s = queue_pop(&(self->queuecant),&cantaux);
			cant = cantaux;
		}else{
			s = queue_pop(&(self->queuecant),&cantaux);
			cant = cant + cantaux;
			if (queue_isempty(self->queuedatetime)){
				s = queue_push(&datesaux,bufferdate);
				s = queue_push(&ccantaux,&cant);
			}
		}		
	}

	s = queue_pop(&(self->queuetemp),&valuesaux);

	while (!queue_isempty(datesaux)){

		s = queue_pop(&datesaux,bufferdate);
		s = queue_pop(&ccantaux,&cantaux);

		values = malloc(cantaux*sizeof(float));

		for(j=0;j<cantaux;j++){
			s = queue_pop(&(self->queuetemp),&valuesaux);
			values[j]=valuesaux;
		}
			
		for (s=0; s<cantaux; s++){
		  smin=s;
		  for (j=s+1; j<cantaux; j++){
		    if(values[j]<values[smin])
		    	smin=j;
		  }
		  valuesaux = values[s];
		  values[s] = values[smin];
		  values[smin] = valuesaux;
		}

		min = values[0];
		max = values[cantaux-1];

		if (cantaux%2 == 0)
			mediana = values[cantaux/2 - 1];
		else
			mediana = values[cantaux/2];

		fprintf(stdout, "%s Max=%.1f Min=%.1f Mediana=%.1f Muestras=%d\n",bufferdate,min,max,mediana,cantaux);
		memset(bufferdate,0,10);
		free(values);


 	} 

	queue_empty(&datesaux);
	queue_empty(&ccantaux);

	return 0;

}

int serverprocess_destroy (serverprocess_t *self){

	queue_empty(&(self->queuetemp));
	queue_empty(&(self->queuedatetime));
	queue_empty(&(self->queuecant));
	datetime_destroy(&(self->datetime));

	return 0;
}		
