
typedef struct {
    FILE* archivo;
    char cadenaleida[80];
    char separador[2];
	int cantmuestrasleidas;
	int cantmuestrasaleer;
    } parser_t;		


int parser_create (parser_t *self, char* file, int step);
int parser_destroy (parser_t *self);


