#include "socket.h"
#include "server.h"
#include "client.h"
#include "fileprocess.h"
#include "serverprocess.h"
#include "datetime.h"
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){

	char *type1 = "server";
	char *type2 = "client";

	int s;

	int step,milisecondstep;

	int cantidad, muestrasobtenidas;

	char* buffer;
	char datetime[20];
 	
 	int seg;

	server_t server;

	client_t client;

	datetime_t date;

	fileprocess_t fprocess;

	serverprocess_t sprocess;

	if (strcmp(argv[1],type1) == 0){	

		if (argc == 3){

			s = serverprocess_create(&sprocess);
			
			s = server_create(&server);

 			s = server_connect(&server,argv[2]);

 			if (s!=0){
 				s = server_destroy(&server);
 				s = serverprocess_destroy(&sprocess); 	
 				return 1;
 			}
 			
 			s = server_receive(&server,&sprocess);

 			s = server_destroy(&server); 	

 			s = serverprocess_destroy(&sprocess);

		} else {

			return 2;
		}
	
	}
	else{
		if (strcmp(argv[1],type2) == 0){

			if (argc == 8){

				milisecondstep = atoi(argv[5]);

				step = milisecondstep/1000;

				muestrasobtenidas = 0;

				s = datetime_create(&date); 

				s = datetime_setdatetime(&date,argv[6]);

				s = datetime_getsecond(&date,&seg);

				s = fileprocess_create(&fprocess,argv[7]);

				if (s!=0){
					s = fileprocess_destroy(&fprocess);
 					s = datetime_destroy(&date);

 					return 2;
				}

 				s = fileprocess_process(&fprocess);

				s = client_create(&client);

   				s = client_connect (&client, argv[2], argv[3]);

   				if (s!=0){
   					s = fileprocess_destroy(&fprocess);
 					s = datetime_destroy(&date);
 					s = client_destroy(&client);
 					return 1;
   				}

 				cantidad = (60-seg)/step + 1;

				buffer = malloc (6*cantidad + 20);

 				memset(buffer,0,6*cantidad + 20);

 				//strncat(buffer,"Recibiendo termostato. ID=",26);
 				strncat(buffer,argv[4],strlen(argv[4]));
 				//strncat(buffer,"\n",1);

 				s = client_send (&client, buffer, 6*cantidad + 20);

 				free(buffer);

 				while (!fileprocess_isempty(&fprocess)){

 					buffer = malloc (6*cantidad + 20);

 					memset(buffer,0,6*cantidad + 20);

 					memset(datetime,0,20);

 					s = datetime_getdatetime (&date, buffer);

 					s = datetime_getdatetime (&date, datetime);

 					s = datetime_minuteincrease (&date);

 					s = fileprocess_getvalues(&fprocess,buffer,cantidad);

 					fprintf(stderr, "%s - Enviando %i muestras\n", datetime,s);

   					s = client_send (&client, buffer, 6*cantidad + 20);
 					
   					cantidad = 60/step;

   					free(buffer);
 				}

 				s = fileprocess_destroy(&fprocess);
 				s = datetime_destroy(&date);
   				s = client_destroy(&client);

			} else {

				return 2;
			}

		}

		else {
			return 2;
		}
	}

	return 0;
}

