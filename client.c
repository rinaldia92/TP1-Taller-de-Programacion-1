#include "client.h"

#define	DATETIMELENGTH 20
#define VALUELENGTH 7

int client_create(client_t *self){
	socket_create(&(self->socket),0);
	datetime_create(&(self->datetime));
	return 0;
}

int client_connect(client_t *self, char *hostname, char *port){
	int s;
	s = socket_connect(&(self->socket), hostname, port);
	if (s != 0){
		socket_shutdown(&(self->socket));
		return 1;
	}
	return 0;
}

int client_setdatetime(client_t *self, char *datetime){
	datetime_setdatetime(&(self->datetime),datetime);
	return 0;
}

int client_setfile(client_t *self, char *file){
	fileprocess_create(&(self->process),file);
	return 0;
}

int client_setstep(client_t *self, char *step){
	self->milisecondstep = atoi(step);
	return 0;
}

int client_sendid(client_t *self, char* buffer, int size){
	socket_send(&(self->socket), buffer, size);
	return 0;
}

int client_send(client_t *self){
	int s;
	int step,seg,cantidad,size;
	char *buffer;
	char datetime[DATETIMELENGTH];
	bool firstlap = true;
	/*firstlap utilizado para chequear si es el primer envio debido
  a que el primer minuto puede no estar completo*/

	step = (self->milisecondstep)/1000;

	datetime_getsecond(&(self->datetime),&seg);

	cantidad = 60/step;
	size = cantidad*VALUELENGTH +DATETIMELENGTH;
	buffer = malloc(size);

	//Seteo la cantidad de elementos a tomar en el primer minuto
	if (seg != 0){
		if ((60-seg)%step != 0)
			cantidad = (60-seg)/step + 1;
		else
			cantidad = (60-seg)/step;
	}

	datetime[0]=0;
	buffer[0]=0;

//Cargo el buffer con las temperaturas y envio mientras el archivo no este vacio
	while (!fileprocess_isempty(&(self->process))){
		datetime_getdatetime(&(self->datetime), buffer,sizeof(datetime));
		datetime_getdatetime(&(self->datetime), datetime,sizeof(datetime));
		datetime_minuteincrease(&(self->datetime));

		s = fileprocess_getvalues(&(self->process),buffer,cantidad);

		if (s != 0){
			fprintf(stderr, "%s - Enviando %i muestras\n", datetime,s);
			socket_send(&(self->socket), buffer, strlen(buffer));
		}
		if (firstlap){
			cantidad = 60/step;
			firstlap = false;
		}
	}
	free(buffer);
	return 0;
}

int client_destroy(client_t *self){
	socket_shutdown(&(self->socket));
	socket_destroy(&(self->socket));
	datetime_destroy(&(self->datetime));
	fileprocess_destroy(&(self->process));
	return 0;
}
