#include <stdio.h>
#include <stdlib.h>

//////////////////////// LINKED LIST DS ////////////////////
typedef struct Node{
	int value;
	Node* next;
};

Node* insertLast(Node* l, int item){
	
	if(l == NULL){
		l = (Node*)malloc(sizeof(Node));
		l->value = item;
		l->next = NULL;	
	}
	else{
		Node* it = l;

		while(it->next != NULL)
			it = it->next;

		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->value = item;
		tmp->next = NULL;

		it->next = tmp;
	}
	return l;
}

Node* insertFirst(Node* l, int item){

	if(l == NULL){
		l = (Node*)malloc(sizeof(Node));
		l->value = item;
		l->next = NULL;
	}
	else{
		Node* tmp = (Node*)malloc(sizeof(Node));
		tmp->value = item;
		tmp->next = l;
		l = tmp;
	}
	return l;
}

Node* removeLast(Node* l, int* item){

	if(l == NULL)
		return l;


	if (l->next == NULL){
		*item = l->value;
		free(l);
		l = NULL;
	}
	else{
		Node* it = l;
		while (it->next->next != NULL)
			it = it->next;

		*item = it->next->value;
		free(it->next);
		it->next = NULL;
	}
	return l;
}

Node* removeFirst(Node* l, int* item){

	if (l == NULL)
		return NULL;


	if (l->next == NULL){
		*item = l->value;
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

Node* find(Node* l, int item){

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

Node* remove(Node* l, int item, bool* status){
	*status = false;
	if (l == NULL)
		return NULL;
	Node* itemToBeRemoved = find(l, item);
	if(itemToBeRemoved == NULL)
		return l;

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

//////////////////////// LINKED LIST DS END //////////////////
///////////////////// Q DS USING LINKED LIST ///////////////////

typedef struct Queue{
	Node* base;
	Queue(){
		base = NULL;
	}
};

bool enqueue(Queue* s, int item){
	s->base = insertFirst(s->base, item);
	if (s->base == NULL)
		return false;
	else
		return true;
}

bool dequeue(Queue* s, int* item){

	if (s->base == NULL)
		return false;
	int tmp;
	s->base = removeLast(s->base, &tmp);
	*item = tmp;
	return true;
}
