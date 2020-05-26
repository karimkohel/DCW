#ifndef linkedQ_H
#define linkedQ_H

//////////////////////// LINKED LIST DS ////////////////////
struct node_t{
	char value;
	int freq; // aka: priority (but in reverse)
	node_t* next;
};

node_t* insertLast(node_t* l, char item){
	
	if(l == NULL){
		l = (node_t*)malloc(sizeof(node_t));
		l->value = item;
		l->next = NULL;
		l->freq = 1;
	}
	else{
		node_t* it = l;

		while(it->next != NULL)
			it = it->next;

		node_t* tmp = (node_t*)malloc(sizeof(node_t));
		tmp->value = item;
		tmp->freq = 1;
		tmp->next = NULL;

		it->next = tmp;
	}

	return l;
}

node_t* insertFirst(node_t* l, char item){

	if(l == NULL){
		l = (node_t*)malloc(sizeof(node_t));
		l->value = item;
		l->next = NULL;
		l->freq = 1;
	}
	else{
		node_t* tmp = (node_t*)malloc(sizeof(node_t));
		tmp->value = item;
		l->freq = 1;
		tmp->next = l;
		l = tmp;
	}
	return l;
}

node_t* removeLast(node_t* l, char* item, int *freq){

	if(l == NULL)
		return l;


	if (l->next == NULL){
		*item = l->value;
		*freq = l->freq;
		free(l);
		l = NULL;
	}
	else{
		node_t* it = l;
		while (it->next->next != NULL)
			it = it->next;

		*item = it->next->value;
		*freq = it->next->freq;
		free(it->next);
		it->next = NULL;
	}
	return l;
}

node_t* removeFirst(node_t* l, char* item, int *freq){

	if (l == NULL)
		return NULL;


	if (l->next == NULL){
		*item = l->value;
		*freq = l->freq;
		free(l);
		l = NULL;
	}
	else{
		*item = l->value;
		node_t* tmp = l->next;
		free(l);
		l = tmp;
	}

	return l;
}

node_t* find(node_t* l, char item, int *freq){

	if (l == NULL)
		return NULL;

	else{
		node_t* it = l;
		while (it != NULL){
			if (it->value == item)
				return it;
			else
				it = it->next;
		}
	}
	return NULL;
}

node_t* remove(node_t* l, char item, int *freq, bool* status){
	*status = false;
	if (l == NULL)
		return NULL;
	node_t* itemToBeRemoved = find(l, item);
	if(itemToBeRemoved == NULL)
		return l;

	*freq = itemToBeRemoved->freq;

	if (l == itemToBeRemoved){

		l = l->next;
		free(itemToBeRemoved);
	}
	else{
		node_t* it = l;
		while (it->next != itemToBeRemoved)
			it = it->next;
		
		node_t* tmp = it->next->next;
		free(itemToBeRemoved);
		it->next = tmp;
	}
	*status = true;
	return l;
}

void switchNodes(node_t *node1, node_t *node2){
	//works only if the two nodes are after each other
	node_t *tmp = node2;
	node2->next = node1;
	node1->next = tmp //need a doubly linked list for that 

}

void organiseList(node_t *head){

	while(head != NULL){

	}
}


//////////////////////// END OF LINKED LIST DS //////////////////
///////////////////// Q DS USING LINKED LIST ///////////////////

struct Queue{
	node_t* base;
	Queue(){
		base = NULL;
	}
};

bool enqueue(Queue* s, char item){

	if(s->base == NULL)
		return false;

	node_t *tmp = find(s->base, item);

	if(tmp == NULL)
		tmp = insertLast(s->base, item, 1); // might change to instertFirst later
		if(tmp == NULL)
			return false;
		s->base = tmp;
	else{
		tmp->freq++;
		//organiseList(s->base); //implement the goddamn function
	}

	return true;
}

bool dequeue(Queue* s, char* item, int *freq){

	if(s->base == NULL)
		return false;

	int freq;
	char character;

	node_t *tmp removeFirst(s->base, &character, &freq);

	return true;
}

///////////////////// END OF Q DS ///////////////////

#endif