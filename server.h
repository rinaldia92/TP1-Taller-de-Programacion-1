#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

typedef struct{
	
	//char *hostname;
	//unsigned short port; 
	struct addrinfo hints;	
	socket_t socket, peerskt;
	char buffer[1000];
	}server_t;


int server_create (server_t *self);

int server_connect (server_t *self, char *port);

int server_receive (server_t *self);

int server_print (server_t *self);

int server_destroy(server_t *self);
