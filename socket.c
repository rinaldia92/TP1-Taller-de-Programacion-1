#include <socket.h>

int socket_create(socket_t *self){
	
	int s;
	bool are_we_connected = false;
	const char *hostname = "www.fi.uba.ar";
   	const char *servicename = "http";

   	struct addrinfo hints;
   	struct addrinfo *result, *ptr;
	
	memset(&hints, 0, sizeof(struct addrinfo));
   	hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   	hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   	hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */

	s = getaddrinfo(hostname, servicename, &hints, &result);

   	if (s != 0) {
   	   printf("Error in getaddrinfo: %s\n", gai_strerror(s));
   	   return 1;
   	}

	for (ptr = result; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
      
      self->socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
      if (self->socket == -1) {
         printf("Error: %s\n", strerror(errno));
      }
      else
      {
     
         s = connect(self->socket, ptr->ai_addr, ptr->ai_addrlen);
         if (s == -1) {
            printf("Error: %s\n", strerror(errno));
            close(self->socket);
         }
         are_we_connected = (s != -1); // nos conectamos?
      }
   }

	return 0;

}



int socket_destroy(socket_t *self){
	close(self->socket);
	return 0;
}

int socket_bind_and_listen(socket_t *self, unsigned short port);
int socket_connect(socket_t *self, const char* host_name, unsigned short port);
int socket_accept(socket_t *self, socket_t* accepted_socket);
int socket_send(socket_t *self, const char* buffer, size_t length);
int socket_receive(socket_t *self, char* buffer, size_t length);
void socket_shutdown(socket_t *self);


