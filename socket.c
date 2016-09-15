#include "socket.h"

#define MAXLISTEN 20

int socket_create(socket_t *self,int type){
   self->socket = 0;

  memset(&self->hints, 0, sizeof(struct addrinfo));
 	self->hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
 	self->hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
 	self->hints.ai_flags = type;     /* None (or AI_PASSIVE for server) */

   return 0;
}

int socket_destroy(socket_t *self){
   if (self->socket == -1){
      socket_shutdown(self);
	   close(self->socket);
   }else{
      socket_shutdown(self);
      close(self->socket);
   }
	return 0;
}

int socket_bind_and_listen(socket_t *self, char* port){
   int s;

   struct addrinfo *ptr;

   s = getaddrinfo(NULL, port, &(self->hints), &ptr);

   self->socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

   s = bind(self->socket, ptr->ai_addr, ptr->ai_addrlen);
   if (s == -1) {
      close(self->socket);
      freeaddrinfo(ptr);
      return 1;
   }

   freeaddrinfo(ptr);

   s = listen(self->socket, MAXLISTEN);
   if (s == -1) {
      close(self->socket);
      return 1;
   }

   return 0;
}

int socket_connect(socket_t *self, const char* host_name, char* port){
   int s;
   bool are_we_connected;

   struct addrinfo *result, *ptr;

   are_we_connected = false;

   s = getaddrinfo(host_name, port, &(self->hints), &result);

   for (ptr = result; ptr != NULL && !are_we_connected; ptr = ptr->ai_next) {
      self->socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

      if (self->socket == -1) {
         return 1;
      }else{
         s = connect(self->socket, ptr->ai_addr, ptr->ai_addrlen);
         if (s == -1) {
            close(self->socket);
            return 1;
         }
         are_we_connected = (s != -1);
      }
   }
   freeaddrinfo(result);
   return 0;
}

int socket_accept(socket_t *self, socket_t* accepted_socket){
   accepted_socket->socket = accept(self->socket, NULL, NULL);

   if (accepted_socket->socket == -1)
      return -1;

   return 0;
}

int socket_send(socket_t *self, const char* buffer, size_t length){
   int s;
   int bytes_sent;
   bool socket_error, remote_socket_closed;

   socket_error = false;
   remote_socket_closed = false;

   bytes_sent = 0;

   while (bytes_sent < length && !socket_error && !remote_socket_closed) {
      s = send(self->socket, &buffer[bytes_sent],
          length - bytes_sent, MSG_NOSIGNAL);

      if (s < 0) {
         socket_error = true;
      }else if (s == 0) {
         remote_socket_closed = true;
      }else {
         bytes_sent += s;
      }
   }

   if (!remote_socket_closed && !socket_error) {
      return bytes_sent;
   }else {
      return -1;
   }
}

int socket_receive(socket_t *self, char* buffer, size_t length){
  int s = 1;
  char aux;
  strncpy(&aux,"",1);
  while (strcmp(&aux,"\n")!=0 && s>0){
    s = recv(self->socket,&aux, 1, MSG_NOSIGNAL);
    strncat(buffer,&aux,1);
  }

  return s;
}

void socket_shutdown(socket_t *self) {
   shutdown(self->socket, SHUT_RDWR);
}
