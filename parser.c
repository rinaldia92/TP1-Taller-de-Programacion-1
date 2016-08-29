


int parser_create (parser_t *self, 	char* file, int step){

	self->archivo = fopen(file, "r");
	self->cantmuestrasaleer = 60000/step;
		


}
int parser_destroy (parser_t *self){
	self->archivo = fclose;
	
}
