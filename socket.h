#ifndef __socket__
#define __socket__

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>




#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

typedef struct {
	int socket;
} socket_t;

int socket_create(socket_t *self);
int socket_destroy(socket_t *self);
int socket_bind_and_listen(socket_t *self, char* port,struct addrinfo *hints);
int socket_connect(socket_t *self, const char* host_name, char* port,struct addrinfo *hints);
int socket_accept(socket_t *self, socket_t* accepted_socket);
int socket_send(socket_t *self, const char* buffer, size_t length);
int socket_receive(socket_t *self, char* buffer, size_t length);
void socket_shutdown(socket_t *self);

#endif