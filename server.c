#include "server.h"

#define	DATETIMELENGTH 20
#define DATELENGTH 12
#define MINMAXMEDLENGTH 100
#define AUXLENGTH 60

int server_create(server_t *self){
	socket_create(&(self->socket),AI_PASSIVE);
	socket_create(&(self->peerskt),AI_PASSIVE);
	datetime_create(&(self->datetime));
	serverprocess_create(&(self->process));
	(self->buffer)[0]=0;
	(self->id)[0]=0;
	return 0;
}

int server_connect(server_t *self, char *port){
	int s;
	s = socket_bind_and_listen(&(self->socket),port);
	if (s != 0){
		socket_shutdown(&(self->socket));
		return 1;
	}

	s = socket_accept(&(self->socket), &(self->peerskt));
	if (s == -1){
		printf("Conexion fallo \n");
		return -1;
	}
	return 0;
}

int server_obtenermediana(server_t *self,char *date){
	char minmanmed[MINMAXMEDLENGTH];
	char minmanmedaux[AUXLENGTH];
	minmanmed[0]=0;
	minmanmedaux[0]=0;

	serverprocess_order(&(self->process));
	serverprocess_getmed(&(self->process),minmanmedaux,AUXLENGTH);
	snprintf(minmanmed,MINMAXMEDLENGTH, "%s %s %s",date,self->id,minmanmedaux);
	fprintf(stdout, "%s\n",minmanmed);
	return 0;
}

//Recibe informacion del socket y la va procesando utilizando los distintos TDA
int server_receive(server_t *self){
	int s = 0;
	int cant = 0;
	int day;
	int dayant;
	char datetime[DATETIMELENGTH];
	char date[DATELENGTH];

	dayant = 0;

	s = socket_receive(&(self->peerskt), self->buffer, strlen(self->buffer));

	strncat(self->id,self->buffer,strlen(self->buffer)-1);
	(self->buffer)[0]=0;
	fprintf(stderr, "Recibiendo termostato. ID=%s\n",self->id);

	s = socket_receive(&(self->peerskt), self->buffer, strlen(self->buffer));

	while (s > 0){
		sscanf(self->buffer,"%s %[^\n]",datetime,self->buffer);
		datetime_setdatetime(&(self->datetime),datetime);
		datetime_getday(&(self->datetime),&day);

		if (day!=dayant){
			if (dayant != 0){
				server_obtenermediana(self,date);
			}
			dayant = day;
		}

		cant = serverprocess_setvalues(&(self->process),self->buffer);

		fprintf(stderr, "%s - Datos recibidos: %d\n",datetime,cant);
		(self->buffer)[0]=0;
		cant = 0;
		datetime_getdate(&(self->datetime),date,sizeof(date));

		s = socket_receive(&(self->peerskt), self->buffer, 2000);
	}

	server_obtenermediana(self,date);

	fprintf(stderr, "Termostato desconectado. ID=%s\n",self->id);
	serverprocess_destroy(&(self->process));
	return 0;
}

int server_destroy(server_t *self){
	datetime_destroy(&(self->datetime));
	socket_shutdown(&(self->socket));
	socket_shutdown(&(self->peerskt));
	socket_destroy(&(self->socket));
	socket_destroy(&(self->peerskt));
	return 0;
}
