#include "socket.h"

int socket_create(socket_t *self){
	
   self->socket = 0;

   return 0;

}


int socket_destroy(socket_t *self){
   if (self->socket == -1){
	   close(self->socket);
   }
   else{
      socket_shutdown(self);
      close(self->socket);
   }
	return 0;
}

int socket_bind_and_listen(socket_t *self, char* port,struct addrinfo *hints){
   
   int s;

   struct addrinfo *ptr; 

   s = getaddrinfo(NULL, port, hints, &ptr);


   self->socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

   // Decimos en que direccion local queremos escuchar, en especial el puerto
   // De otra manera el sistema operativo elegiria un puerto random
   // y el cliente no sabria como conectarse
   s = bind(self->socket, ptr->ai_addr, ptr->ai_addrlen);
   if (s == -1) {
      //printf("Error: %s\n", strerror(errno));
      close(self->socket);
      freeaddrinfo(ptr);
      return 1;
   }

   freeaddrinfo(ptr);

   // Cuanto clientes podemos mantener en espera antes de poder acceptarlos?
   s = listen(self->socket, 20);
   if (s == -1) {
      //printf("Error: %s\n", strerror(errno));
      close(self->socket);
      return 1;
   }

   return 0;

}
int socket_connect(socket_t *self, const char* host_name, char* port,struct addrinfo *hints){

   int s;
   bool are_we_connected;

   struct addrinfo *result, *ptr; 

   are_we_connected = false;

   s = getaddrinfo(host_name, port, hints, &result);

   for (ptr = result; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
         
      self->socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

      if (self->socket == -1) {
         //printf("Error: %s\n", strerror(errno));
         return 1;
      }
      else
      {
         s = connect(self->socket, ptr->ai_addr, ptr->ai_addrlen);
         if (s == -1) {
            //printf("Error: %s\n", strerror(errno));
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
   bool is_there_a_socket_error, is_the_remote_socket_closed;

   is_there_a_socket_error = false;
   is_the_remote_socket_closed = false;

   bytes_sent = 0;

   /* Enviamos el mensaje intentando enviar todo el mensaje de un solo intento,
      y solo reintentando enviar aquellos bytes que no pudiero entrar */
   while (bytes_sent < length && is_there_a_socket_error == false && is_the_remote_socket_closed == false) {
      s = send(self->socket, &buffer[bytes_sent], length - bytes_sent, MSG_NOSIGNAL);

      if (s < 0) {  // ups,  hubo un error
         //printf("Error: %s\n", strerror(errno));
         is_there_a_socket_error = true;
      }
      else if (s == 0) { // nos cerraron el socket :(
         is_the_remote_socket_closed = true;
      }
      else {
         bytes_sent += s;
      }
   }

   if (!is_the_remote_socket_closed) {
      return bytes_sent;
   }
   else {
      return -1;
   }

}



int socket_receive(socket_t *self, char* buffer, size_t length){

   int received = 0;
   int s = 0;
   bool is_the_socket_valid = true;

   //while (received < length && is_the_socket_valid) {

      s = recv(self->socket, &buffer[0], length-received -1, MSG_NOSIGNAL);
      
      if (s == 0) { // nos cerraron el socket :(
         is_the_socket_valid = false;
      }
      else if (s < 0) { // hubo un error >(
         is_the_socket_valid = false;
      }
      else {
         received += s;
         //printf("%s\n",buffer);
         //memset(&buffer[0],0,strlen(buffer));
      } 

   //}

   if (is_the_socket_valid) {
      return received;
   }
   else {
      return -1;
   }

}


void socket_shutdown(socket_t *self) {

   shutdown(self->socket, SHUT_RDWR);
   
}


