#ifndef __QUEUE__
	#define __QUEUE__

	#include <stdlib.h>
	#include <memory.h>
	#include <stdbool.h>
	
	typedef struct 
	{
		void* elem;
		struct queuenode *sig;
	} queuenode;
	
	typedef struct
	{
		queuenode *first, *last;
		int datasize;
	} queue_t;
	
	void queue_create(queue_t *self, int datasize);
	void queue_empty(queue_t *self);
	bool queue_isempty(queue_t self);
	int queue_push(queue_t *self, void* elem);
	int queue_pop(queue_t *self, void* elem);
#endif

