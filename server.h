#include "socket.h"
#include "datetime.h"
#include "serverprocess.h"
#include <stdio.h>

#define MAXLENGTH 2000
#define IDLENGTH 200

typedef struct{
	socket_t socket, peerskt;
	datetime_t datetime;
	serverprocess_t process;
	char buffer[MAXLENGTH];
	char id[IDLENGTH];
	}server_t;

//Inicializa la estructura del server
int server_create(server_t *self);

//Utiliza funciones del TDA socket para enlazarse con un cliente
int server_connect(server_t *self, char *port);

//Funcion interna para calcular max, min y mediana usando el TDA serverprocess
int server_obtenermediana(server_t *self,char *date);

/*Recibe informacion del cliente y  procesa utilizando TDA serverprocess y
TDA datetime el cual procesa la informacion entrante y devuelve la cantidad de
elementos recibidos y resumen por dia */
int server_receive(server_t *self);

// Destruye los elementos de la estructura
int server_destroy(server_t *self);
