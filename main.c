#include "socket.h"
#include "server.h"
#include "client.h"
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define REQUEST_MAX_LEN 128
#define RESPONSE_MAX_LEN 1024

int main (int argc, char *argv[]){

	char *type = "server";

	int s;

	char* request;
 	int request_len;

	server_t server;

	client_t client;

	if (strcmp(argv[1],type) == 0){	
		
		s = server_create(&server);

 		s = server_connect(&server,argv[2]);
 	
 		s = server_receive(&server); 

 		s = server_destroy(&server); 	
	
	}
	else{

		s = client_create(&client);

   		s = client_connect (&client, argv[2], argv[3]);

   		request = "Felix PUTO \n";

   		request_len = strlen(request);

   		s = client_send (&client, request, request_len);

   		s = client_destroy(&client);

	}

	// int s = 0;
   	/*bool are_we_connected = false;
   	bool is_there_a_socket_error = false;
   	bool is_the_remote_socket_closed = false;
*/
 //   	char request[REQUEST_MAX_LEN];
 //   	int request_len;
 //   	char response[RESPONSE_MAX_LEN];

 //   	// A quien nos queremos conectar
 //   	char *hostname = "www.fi.uba.ar";
 //   	const char *servicename = "http";

 //   	client_t client;
	
 //   	s = client_create(&client);

 //   	s = client_connect (&client, hostname, 80);

	// snprintf(request, REQUEST_MAX_LEN, "GET /es/node/%s HTTP/1.1\r\nHost: www.fi.uba.ar\r\n\r\n", argv[1]);
 //   	request[REQUEST_MAX_LEN-1] = 0;
 //   	request_len = strlen(request);

 //   	s = client_send (&client, request, request_len);
   
 //   	if (is_the_remote_socket_closed || is_there_a_socket_error) {
 //      s = client_destroy(&client);
 //      return 1;
 //   	}

 //   	s = client_receive(&client);

 //   	s = client_destroy(&client);


  //  	int s;

  

   	// client_t client;

   	
   
   	// if (is_the_remote_socket_closed || is_there_a_socket_error) {
    //   s = client_destroy(&client);
    //   return 1;
   	// }

   	// //s = client_receive(&client);

   	// s = client_destroy(&client);

	return 0;
}

