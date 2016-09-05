#include "socket.h"
#include "serverprocess.h"
#include "datetime.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

typedef struct{ 
	struct addrinfo hints;	
	socket_t socket, peerskt;
	char buffer[2000];
	}server_t;


int server_create (server_t *self);

int server_connect (server_t *self, char *port);

int server_receive (server_t *self,serverprocess_t *process);

int server_print (server_t *self);

int server_destroy(server_t *self);
