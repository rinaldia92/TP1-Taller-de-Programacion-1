#include "socket.h"
#include "datetime.h"
#include "fileprocess.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

typedef struct{
	struct addrinfo hints;
	socket_t socket;
	datetime_t datetime;
	fileprocess_t process;
	int milisecondstep;
	char buffer[2000];
	}client_t;


int client_create(client_t *self);

int client_connect(client_t *self, char *hostname, char *port);

int client_setdatetime(client_t *self, char *datetime);

int client_setfile(client_t *self, char *file);

int client_setstep(client_t *self, char *step);

int client_sendid(client_t *self, char* buffer, int size);

int client_send(client_t *self);//, char* buffer, int size);

int client_receive(client_t *self);

int client_destroy(client_t *self);
