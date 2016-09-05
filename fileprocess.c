#include "fileprocess.h"


int fileprocess_create (fileprocess_t *self, 	char* file){
	
	self->arch = fopen(file, "rb");
	queue_create(&(self->queue),sizeof(float));

	if (self->arch)
		return 0;
	else
		return 1;
}

int fileprocess_process(fileprocess_t *self){
	int s;
	short value;
	float prevvalue,currentvalue;

	prevvalue = 0.0;

	while (!feof(self->arch)){
      fread(&value,sizeof(short),1,self->arch);
      if (htons(value) > 0x02ff){
      	s=queue_push(&(self->queue),&prevvalue);
      } else {
      	currentvalue = -17.0 + 0.1*htons(value);
      	prevvalue = currentvalue;
      	s=queue_push(&(self->queue),&currentvalue);
      }
   }
	return 0;
}

int fileprocess_getvalues(fileprocess_t *self, char* elem, int cant){

	int s,i;
	float value;
	char cvalue[5];
	strncat(elem," ",1);
	for (i = 0; i<cant ; i++){
		if(!queue_isempty(self->queue)){
			s=queue_pop(&(self->queue),&value);
			sprintf(cvalue, "%.1f", value);
			strncat(elem,cvalue,sizeof(cvalue));
			
			if (i!=cant-1){
				if (!queue_isempty(self->queue)){
					strncat(elem," ",1);
				} else{
					strcat(elem,"\n");
					return i+1;
				}	
			} else {
				strcat(elem,"\n");
				return i+1;
			}

			
		}

	}

}

int fileprocess_destroy (fileprocess_t *self){
	fclose(self->arch);
	queue_empty(&(self->queue));
	return 0;
}

bool fileprocess_isempty(fileprocess_t *self){

	return queue_isempty(self->queue);
}