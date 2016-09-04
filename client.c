#include "client.h"


int client_create (client_t *self){
	
	//self->port = port;

	memset(&self->hints, 0, sizeof(struct addrinfo));
   	self->hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   	self->hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   	self->hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */
	
	socket_create(&(self->socket));

	return 0;

}

int client_connect (client_t *self, char *hostname, char *port){

	int s;

	s = socket_connect(&(self->socket), hostname, port, &(self->hints));

	if (s == 0)
		printf("Conexion exitosa \n");
	else{
		socket_shutdown(&(self->socket));
		return 1;
	}

	return 0;
}


int client_send (client_t *self, char* buffer, int size){

	int s;
	s = socket_send(&(self->socket), buffer, size);
	return 0;
}

int client_receive (client_t *self){

	int s;
	s = socket_receive(&(self->socket), self->buffer, 100);

	return 0;
}

int client_destroy(client_t *self){

	int s;

	socket_shutdown(&(self->socket));

	s=socket_destroy(&(self->socket));

	return 0;
}