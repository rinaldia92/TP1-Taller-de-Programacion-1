#include <stddef.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int socket;
} socket_t;

int socket_create(socket_t *self);
int socket_destroy(socket_t *self);
int socket_bind_and_listen(socket_t *self, unsigned short port);
int socket_connect(socket_t *self, const char* host_name, unsigned short port);
int socket_accept(socket_t *self, socket_t* accepted_socket);
int socket_send(socket_t *self, const char* buffer, size_t length);
int socket_receive(socket_t *self, char* buffer, size_t length);
void socket_shutdown(socket_t *self);

