#include "queue.h"

void queue_create(queue_t *self, int datasize)
{
	self->first = self->last = NULL;
	self->datasize = datasize;
}

void queue_empty(queue_t *self)
{
	queuenode *aux = self->first;
	queuenode *sig;
	while (aux)
	{
		sig = aux->sig;
		free(aux->elem);
		free(aux);
		aux = sig;
	}
	self->first = self->last = NULL;
}


bool queue_isempty(queue_t self)
{
	return (self.first==NULL);
}


int queue_push(queue_t *self, void* pE)
{
	queuenode *node = (queuenode*) malloc(sizeof(queuenode));
	if (!node)
		return 1;
	else
	{
		if (self->last)
			self->last->sig = node;
		if (!self->first) /*Est� vac�a*/
			self->first = node;
		node->sig = NULL;
		self->last = node;
		node->elem = malloc (self->datasize);
		if(!node->elem)
		{
			free(node);
			return 1;
		}
		memcpy(node->elem, pE, self->datasize);
		return 0;
	}
}

int queue_pop(queue_t *self, void* pE)
{
	queuenode *aux = self->first;
	if (!self->first)
		return 1;
	self->first = self->first->sig;
	if (!self->first)
	{
		self->last = NULL;
	}
	memcpy(pE, aux->elem, self->datasize);
	free(aux->elem);
	free(aux);
	return 1;
}

