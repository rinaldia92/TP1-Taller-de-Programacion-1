#include "socket.h"
#include "server.h"
#include "client.h"
//#include "fileprocess.h"
//#include "serverprocess.h"
#include "datetime.h"
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	char *type1 = "server";
	char *type2 = "client";
	int s;
	char buffer[25];
	server_t server;
	client_t client;

	if (strcmp(argv[1],type1) == 0){
		 if (argc == 3){
		 	s = server_create(&server);
 	 		s = server_connect(&server,argv[2]);

 			if (s!=0){
 				s = server_destroy(&server);
 				return 1;
 			}

 			s = server_receive(&server);
 			s = server_destroy(&server);
		} else {
			return 2;
		}
	}else{
		if (strcmp(argv[1],type2) == 0){
			if (argc == 8){
				s = client_create(&client);
				s = client_setdatetime(&client, argv[6]);
				s = client_setfile(&client,argv[7]);
				s = client_setstep(&client,argv[5]);
 				s = client_connect(&client, argv[2], argv[3]);

 				if (s!=0){
					s = client_destroy(&client);
					return 1;
 				}

 				memset(buffer,0,25);

 				strncat(buffer,argv[4],strlen(argv[4]));
				strncat(buffer,"\n",1);

 			  client_sendid(&client, buffer,strlen(buffer));
				client_send(&client);
   			client_destroy(&client);
			} else {
				return 2;
			}
		} else {
			return 2;
		}
	}

	return 0;
}
