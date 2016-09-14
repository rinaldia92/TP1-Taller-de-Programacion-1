#include "client.h"

int client_create(client_t *self){
	memset(&self->hints, 0, sizeof(struct addrinfo));
 	self->hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
 	self->hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
 	self->hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

	socket_create(&(self->socket));
	datetime_create(&(self->datetime));

	return 0;
}

int client_connect(client_t *self, char *hostname, char *port){
	int s;

	s = socket_connect(&(self->socket), hostname, port, &(self->hints));

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
	int step,seg,cantidad;
	char *buffer;
	char datetime[25];

	step = (self->milisecondstep)/1000;

	datetime_getsecond(&(self->datetime),&seg);

	cantidad = 60/step;
	buffer = malloc(7*cantidad + 25);
	if (seg != 0){
		if ((60-seg)%step != 0)
			cantidad = (60-seg)/step + 1;
		else
			cantidad = (60-seg)/step;
	}

	while (!fileprocess_isempty(&(self->process))){
		memset(buffer,0,7*cantidad + 25);

		memset(datetime,0,25);

		datetime_getdatetime(&(self->datetime), buffer);

		datetime_getdatetime(&(self->datetime), datetime);

		datetime_minuteincrease(&(self->datetime));

		s = fileprocess_getvalues(&(self->process),buffer,cantidad);

		if (s != 0){
			fprintf(stderr, "%s - Enviando %i muestras\n", datetime,s);
			socket_send(&(self->socket), buffer, strlen(buffer));
		}

		cantidad = 60/step;
	}
	free(buffer);

	return 0;
}

int client_receive(client_t *self){
	socket_receive(&(self->socket), self->buffer, 100);

	return 0;
}

int client_destroy(client_t *self){
	socket_shutdown(&(self->socket));
	socket_destroy(&(self->socket));
	datetime_destroy(&(self->datetime));
	fileprocess_destroy(&(self->process));

	return 0;
}
