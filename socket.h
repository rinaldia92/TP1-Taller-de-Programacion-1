#ifndef __socket__
#define __socket__

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
	int socket;
	struct addrinfo hints;
} socket_t;

//Inicializa la estructura
int socket_create(socket_t *self,int type);
//Destruye los elementos de la estructura
int socket_destroy(socket_t *self);
/*Seteamos en que puerto queremos escuchar y cuantos clientes podemos mantener
en espera antes de aceptar a alguno*/
int socket_bind_and_listen(socket_t *self, char* port);
//Elije la direccion que mejor funcione para poder conectarse
int socket_connect(socket_t *self, const char* host_name, char* port);
//Acepta un cliente
int socket_accept(socket_t *self, socket_t* accepted_socket);
//Envia el buffer a traves de la red
int socket_send(socket_t *self, const char* buffer, size_t length);
//Recibe informacion a traves de la red y lo guarda en el buffer
int socket_receive(socket_t *self, char* buffer, size_t length);
//Cierra la conexion del socket
void socket_shutdown(socket_t *self);

#endif
