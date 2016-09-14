#include "socket.h"
#include "datetime.h"
#include "serverprocess.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

typedef struct{
	struct addrinfo hints;
	socket_t socket, peerskt;
	datetime_t datetime;
	serverprocess_t process;
	char buffer[2000];
	char id[200];
	}server_t;


int server_create(server_t *self);
int server_connect(server_t *self, char *port);
int server_receive(server_t *self);
int server_destroy(server_t *self);
