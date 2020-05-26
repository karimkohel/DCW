#ifndef linkedQ_H
#define linkedQ_H

//////////////////////// LINKED LIST DS ////////////////////

struct node_t {
	 char data;
	 int freq;
	node_t *next;
	node_t *prev;
};

node_t *create_node(char item){

	node_t *node = (node_t*)malloc(sizeof(node_t));

	if(node == NULL)
		return NULL;

	node->data = item;
	node->freq = 1;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

node_t *find_node(node_t *head, char vlu){
	while(head != NULL){
		if(head->data == vlu)
			return head;
		head = head->next;
	}
	return NULL;
}

void print_list(node_t *head){
	while(head != NULL){
		printf("%d-",head->data);
		head = head->next;
	}
	printf("\n");
}

bool insert_first(node_t **head, node_t **tail, char item){

	//whatever the case, we would need to create a node and since it's
	// gonna be the first node, the prev ptr surely will be a NULL
	node_t *tmp = create_node(item);

	if(tmp == NULL)
		return false;

	tmp->prev = NULL;

	if(*head == NULL){
		tmp->next = NULL;
		*tail = tmp;
	}
	else
		tmp->next = *head;

	*head = tmp;

	return true;
}

bool insert_last(node_t **head, node_t **tail, char item){

	//whatever the case, we would need to create a node and since it's
	// gonna be the last node, the next ptr surely will be a NULL
	node_t *tmp = create_node(item);

	if(tmp == NULL)
		return false;

	tmp->next = NULL;

	if(*head == NULL){
		tmp->prev = NULL;
		*head = tmp;
		*tail = tmp;
	}
	else{
		tmp->prev = *tail;
		(*tail)->next = tmp; //needed the paranthesis because pointers are dumb aren't they
		*tail = tmp;
	}

	return true;
}

bool remove_last(node_t **head, node_t **tail, char *element){

	if(*head == NULL)
		return false;

	*element = (*tail)->data;

	if((*head)->next == NULL){
		free((*head));
		*head = NULL;
		*tail = NULL;
	}
	else{
		*tail = (*tail)->prev; //set the tail to the prev node as to prepare for deleting the last node
		free((*tail)->next); //deleted the last node
		(*tail)->next = NULL; //now that thats the last node make the next points to null
	}
	return true;
}

bool remove_first(node_t **head, node_t **tail, char *element){

	if(*head == NULL)
		return false;

	*element = (*head)->data;

	if((*head)->next == NULL){
		free(*head);
		*head = NULL;
		*tail = NULL;
	}
	else{
		*head = (*head)->next;
		free((*head)->prev); // same as last function but from the other end
		(*head)->prev = NULL;
	}
	return true;
}

bool remove_node(node_t **head, node_t **tail, char node_data){

	if(*head == NULL)
		return false;

	node_t *tmp = find_node((*head), node_data);

	if(tmp == NULL)
		return false;

	if(tmp->prev == NULL){
		*head = tmp->next;
		free((*head)->prev);
		(*head)->prev = NULL;
	}
	else if(tmp->next == NULL){
		*tail = tmp->prev;
		free((*tail)->next);
		(*tail)->next = NULL;
	}
	else{
	
		(tmp->prev)->next = tmp->next; //the peranthesis here are not a must but i let them be for readability and
		(tmp->next)->prev = tmp->prev; // to clarify that i am accesing the next and prev nodes's next and prev ptr
		free(tmp);
	}
	return true;
}

void remove_duplicates(node_t **head, node_t **tail){

	node_t *tmp = *head;
	node_t *inner_tmp;
	node_t *to_remove;

	while(tmp != NULL){

		inner_tmp = tmp->next;

		to_remove = find_node(inner_tmp, tmp->data);

		if(to_remove != NULL)
			remove_node(head, tail, to_remove->data);

		tmp = tmp->next;
	}
}


//////////////////////// END OF LINKED LIST DS //////////////////
///////////////////// Q DS USING LINKED LIST ///////////////////

struct Q_t{
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