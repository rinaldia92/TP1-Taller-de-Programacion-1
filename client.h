#include "socket.h"
#include "datetime.h"
#include "fileprocess.h"
#include <stdio.h>

#define MAXLENGTH 2000

typedef struct{
	socket_t socket;
	datetime_t datetime;
	fileprocess_t process;
	int milisecondstep;
	char buffer[MAXLENGTH];
	}client_t;

//Inicializa la estructura
int client_create(client_t *self);

//Utiliza funciones del TDA socket para enlazarse con un server
int client_connect(client_t *self, char *hostname, char *port);

//Utiliza TDA datetime para setear fecha y hora
int client_setdatetime(client_t *self, char *datetime);

//Utiliza TDA fileprocess para setear el archivo a abrir
int client_setfile(client_t *self, char *file);

//Setea cada cuantos milisegundos se envia una temperatura
int client_setstep(client_t *self, char *step);

//Envia el ID del termostato al server
int client_sendid(client_t *self, char* buffer, int size);

/*Prepara el array con las temperaturas utilizando TDA fileprocess
 y con fecha y hora correspondiente usando TDA datetime y lo envia al server */
int client_send(client_t *self);

//Destruye todos los elementos de la estructura
int client_destroy(client_t *self);
