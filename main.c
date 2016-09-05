#include "socket.h"
#include "server.h"
#include "client.h"
#include "fileprocess.h"
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
 	
 	int year,month,day,hour,min,seg;
	char cyear[4],cmonth[2],cday[2],chour[2],cmin[2],cseg[2];


	server_t server;

	client_t client;

	datetime_t date;

	fileprocess_t process;

	if (strcmp(argv[1],type1) == 0){	

		if (argc == 3){
			
			s = server_create(&server);

 			s = server_connect(&server,argv[2]);

 			if (s!=0)
 				return 1;
 	
	 		s = server_receive(&server); 

 			s = server_destroy(&server); 	

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

				sscanf(argv[6],"%[^.].%[^.].%[^-]-%[^:]:%[^:]:%s",cyear,cmonth,cday,chour,cmin,cseg);

				year = atoi(cyear);  
				month  = atoi(cmonth);
				day  = atoi(cday);
				hour  = atoi(chour);
				min  = atoi(cmin);
				seg  = atoi(cseg); 

				s = datetime_create(&date); 

				datetime_setyear(&date, year);
			    datetime_setmonth(&date, month);
			    datetime_setday(&date,day);
			    datetime_sethour(&date, hour);
			    datetime_setmin(&date, min);
			    datetime_setsec(&date,seg);

				s = fileprocess_create(&process,argv[7]);

				if (s!=0)
 					return 2;

 				s = fileprocess_process(&process);

				s = client_create(&client);

   				s = client_connect (&client, argv[2], argv[3]);

   				if (s!=0)
 					return 1;

 				cantidad = (60-seg)/step + 1;

 				while (!fileprocess_isempty(&process)){

 					buffer = malloc (6*cantidad + 20);

 					s = datetime_getdatetime (&date, buffer);

 					s = datetime_minuteincrease (&date);

 					s = fileprocess_getvalues(&process,buffer,cantidad);

   					s = client_send (&client, buffer, strlen(buffer));

   					cantidad = 60/step;

   					free(buffer);
 				}

 				
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

