#ifndef linkedQ_H
#define linkedQ_H

//////////////////////// LINKED LIST DS ////////////////////
struct Node{
	char value;
	int freq;
	Node* next;
};

Node* insertLast(Node* l, char item, int freq){
	
	if(l == NULL){
		l = (Node*)malloc(sizeof(Node));
		l->value = item;
		l->next = NULL;
		l->freq = freq;
	}
	else{
		Node* it = l;

		while(it->next != NULL)
			it = it->next;

		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->value = item;
		tmp->freq = freq;
		tmp->next = NULL;

		it->next = tmp;
	}
	return l;
}

Node* insertFirst(Node* l, char item, int freq){

	if(l == NULL){
		l = (Node*)malloc(sizeof(Node));
		l->value = item;
		l->next = NULL;
		l->freq = freq;
	}
	else{
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->value = item;
		l->freq = freq;
		tmp->next = l;
		l = tmp;
	}
	return l;
}

Node* removeLast(Node* l, char* item, int *freq){

	if(l == NULL)
		return l;


	if (l->next == NULL){
		*item = l->value;
		*freq = l->freq;
		free(l);
		l = NULL;
	}
	else{
		Node* it = l;
		while (it->next->next != NULL)
			it = it->next;

		*item = it->next->value;
		*freq = it->next->freq;
		free(it->next);
		it->next = NULL;
	}
	return l;
}

Node* removeFirst(Node* l, char* item, int *freq){

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
		Node* tmp = l->next;
		free(l);
		l = tmp;
	}

	return l;
}

Node* find(Node* l, char item){

	if (l == NULL)
		return NULL;
	else{
		Node* it = l;
		while (it != NULL){
			if (it->value == item)
				return it;
			else
				it = it->next;
		}
	}
	return NULL;
}

Node* remove(Node* l, char item, int *freq, bool* status){
	*status = false;
	if (l == NULL)
		return NULL;
	Node* itemToBeRemoved = find(l, item);
	if(itemToBeRemoved == NULL)
		return l;

	*freq = itemToBeRemoved->freq;

	if (l == itemToBeRemoved){

		l = l->next;
		free(itemToBeRemoved);
	}
	else{
		Node* it = l;
		while (it->next != itemToBeRemoved)
			it = it->next;
		
		Node* tmp = it->next->next;
		free(itemToBeRemoved);
		it->next = tmp;
	}
	*status = true;
	return l;
}

//////////////////////// END OF LINKED LIST DS //////////////////
///////////////////// Q DS USING LINKED LIST ///////////////////

struct Queue{
	Node* base;
	Queue(){
		base = NULL;
	}
};

bool enqueue(Queue* s, char item){
	s->base = insertFirst(s->base, item);
	if (s->base == NULL)
		return false;
	else
		return true;
}

bool dequeue(Queue* s, char* item){

	if (s->base == NULL)
		return false;
	int tmp;
	s->base = removeLast(s->base, &tmp);
	*item = tmp;
	return true;
}

///////////////////// END OF Q DS ///////////////////

#endif