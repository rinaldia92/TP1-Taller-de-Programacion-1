#include "server.h"


int server_create (server_t *self){

	memset(&self->hints, 0, sizeof(struct addrinfo));
   	self->hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   	self->hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   	self->hints.ai_flags = AI_PASSIVE;              /* None (or AI_PASSIVE for server) */
	
	socket_create(&(self->socket));
	socket_create(&(self->peerskt));

	return 0;

}

int server_connect (server_t *self, char *port){

	int s;

	s = socket_bind_and_listen(&(self->socket),port,&(self->hints));

	if (s == 0)
		printf("Conexion exitosa \n");
	else{
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


int server_receive (server_t *self){

	int s = 0;
	s = socket_receive(&(self->peerskt), self->buffer, 10000);

	return 0;
}

int server_print (server_t *self){

	printf("%s \n",self->buffer);

	return 0;
}


int server_destroy(server_t *self){

	socket_shutdown(&(self->socket));

	return 0;
}


