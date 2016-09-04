#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

typedef struct{
	
	//char hostname[30];
	//unsigned short port; 
	struct addrinfo hints;	
	socket_t socket;
	char buffer[2000];
	}client_t;


int client_create (client_t *self);

int client_connect (client_t *self, char *hostname, char *port);

int client_send (client_t *self, char* buffer, int size);

int client_receive (client_t *self);

int client_destroy(client_t *self);
