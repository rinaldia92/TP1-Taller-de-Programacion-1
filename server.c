#include "server.h"


int server_create(server_t *self){
	//int s;
	memset(&self->hints, 0, sizeof(struct addrinfo));
	self->hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
	self->hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
	self->hints.ai_flags = AI_PASSIVE;     /* None (or AI_PASSIVE for server) */

	socket_create(&(self->socket));
	socket_create(&(self->peerskt));
	datetime_create(&(self->datetime));
	//s = serverprocess_create(&(self->process));
	memset(self->id,0,20);

	return 0;
}


int server_connect(server_t *self, char *port){
	int s;

	s = socket_bind_and_listen(&(self->socket),port,&(self->hints));

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

/*Recibe informacion del cliente y se lo envia al tda serverprocess
  el cual procesa la informacion entrante y devuelve la cantidad de elementos recibidos
*/
int server_receive(server_t *self){
	int s = 0;
	int i = 0;
	int cant = 0;
	int day;
	int dayant;
	char datetime[20];
	char date[12];
	float value;
	char cvalue[7];
	char *aux = "";
	char minmanmed[100];
	char minmanmedaux[60];
	int firstlap;

	memset(minmanmed,0,100);
	memset(minmanmedaux,0,60);

	serverprocess_create(&(self->process));
	dayant = 0;
	firstlap = 0;
	memset(self->buffer,0,2000);
	s = socket_receive(&(self->peerskt), self->buffer, 2000);

	while (s > 0){
		if (i == 0){
			strncat(self->id,self->buffer,strlen(self->buffer)-1);
			memset(self->buffer,0,2000);
			fprintf(stderr, "Recibiendo termostato. ID=%s\n",self->id);
			i++;
		}else{
			sscanf(self->buffer,"%s %[^\n]",datetime,self->buffer);
			datetime_setdatetime(&(self->datetime),datetime);
			datetime_getday(&(self->datetime),&day);

			if (day!=dayant){
				dayant = day;
				if (firstlap != 0){
					serverprocess_order(&(self->process));
					strncat(minmanmed,date,strlen(date));
					strncat(minmanmed," ",1);
					strncat(minmanmed,self->id,strlen(self->id));
					serverprocess_getmed(&(self->process),minmanmedaux);
					strncat(minmanmed,minmanmedaux,strlen(minmanmedaux));
					printf("%s\n",minmanmed);
					memset(minmanmedaux,0,60);
					memset(minmanmed,0,100);
				}
				firstlap = 1;
			}

			while (strlen(self->buffer)> 6){
				sscanf(self->buffer,"%s %[^\n]",cvalue,self->buffer);
				value = strtof(cvalue,&aux);
				serverprocess_setvalues(&(self->process),value);
				cant++;
			}
			sscanf(self->buffer,"%s %[^\n]",cvalue,self->buffer);
			value = strtof(cvalue,&aux);
			serverprocess_setvalues(&(self->process),value);
			cant++;

			fprintf(stderr, "%s - Datos recibidos: %d\n",datetime,cant);
			memset(self->buffer,0,7*cant);
			cant = 0;
			memset(date,0,12);
			datetime_getdate(&(self->datetime),date);
		}
		s = socket_receive(&(self->peerskt), self->buffer, 2000);
	}

	serverprocess_order(&(self->process));
	strncat(minmanmed,date,strlen(date));
	strncat(minmanmed," ",1);
	strncat(minmanmed,self->id,strlen(self->id));
	serverprocess_getmed(&(self->process),minmanmedaux);
	strncat(minmanmed,minmanmedaux,strlen(minmanmedaux));
	fprintf(stdout, "%s\n",minmanmed);
	memset(minmanmedaux,0,60);
	memset(minmanmed,0,100);

	fprintf(stderr, "Termostato desconectado. ID=%s\n",self->id);
	serverprocess_destroy(&(self->process));
	return 0;
}

int server_destroy(server_t *self){
	//int s;

	//s = serverprocess_destroy(&(self->process));
	datetime_destroy(&(self->datetime));
	socket_shutdown(&(self->socket));
	socket_shutdown(&(self->peerskt));

	return 0;
}
