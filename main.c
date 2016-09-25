#include "socket.h"
#include "server.h"
#include "client.h"
#include "datetime.h"
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLIENT "client"
#define SERVER "server"
#define MAXBUFFER 25
#define EXITO 0
#define ERROR_CONEXION 1
#define ARGUMENTOS_INVALIDOS 2

int main(int argc, char *argv[]){
	int s;
	char buffer[MAXBUFFER];
	server_t server;
	client_t client;

	if (strcmp(argv[1],SERVER) == 0){
		 if (argc == 3){
		 	s = server_create(&server);
 	 		s = server_connect(&server,argv[2]);

 			if (s!=0){
 				s = server_destroy(&server);
 				return ERROR_CONEXION;
 			}

 			s = server_receive(&server);
 			s = server_destroy(&server);
		} else {
			return ARGUMENTOS_INVALIDOS;
		}
	}else{
		if (strcmp(argv[1],CLIENT) == 0){
			if (argc == 8){
				s = client_create(&client);
				s = client_setdatetime(&client, argv[6]);
				s = client_setfile(&client,argv[7]);
				s = client_setstep(&client,argv[5]);
 				s = client_connect(&client, argv[2], argv[3]);

 				if (s!=0){
					s = client_destroy(&client);
					return ERROR_CONEXION;
 				}

				buffer[0]=0;
 				strncat(buffer,argv[4],strlen(argv[4]));
				strncat(buffer,"\n",1);

 			  client_sendid(&client, buffer,strlen(buffer));
				client_send(&client);
   			client_destroy(&client);
			} else {
				return ARGUMENTOS_INVALIDOS;
			}
		} else {
			return ARGUMENTOS_INVALIDOS;
		}
	}
	return EXITO;
}
