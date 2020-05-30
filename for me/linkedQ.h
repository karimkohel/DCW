#ifndef linkedQ_H
#define linkedQ_H

//////////////////////// LINKED LIST DS ////////////////////

struct node_t {
	char data;
	int freq;
	node_t *next;
	node_t *prev;
	node_t *left;
	node_t *right;
	// a frankenstein structure
};

node_t *create_node(char item){

	node_t *node = (node_t*)malloc(sizeof(node_t));

	if(node == NULL)
		return NULL;

	node->data = item;
	node->freq = 1;
	node->next = NULL;
	node->prev = NULL;
	node->right = NULL;
	node->left = NULL;

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
		printf("(%c-%d)->",head->data, head->freq);
		head = head->next;
	}
	printf("NULL\n");
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

bool remove_last(node_t **head, node_t **tail, char *element, int *freq){

	if(*head == NULL)
		return false;

	*element = (*tail)->data;
	*freq = (*tail)->freq;

	if((*head)->next == NULL){
		free((*head));
		*head = NULL;
		*tail = NULL;
	}
	else{
		*tail = (*tail)->prev;
		free((*tail)->next);
		(*tail)->next = NULL;
	}

	return true;
}

bool remove_first(node_t **head, node_t **tail, char *element, int *freq){

	if(*head == NULL)
		return false;

	*element = (*head)->data;
	*freq = (*head)->freq;

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

	//Not Applicable for a priority Q

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

void swap_nodes(node_t *node1, node_t *node2){

	// int tmp_freq = node1->freq;
	// char tmp_data = node1->data;

	// node1->data = node2->data;
	// node1->freq = node2->freq;

	// node2->data = tmp_data;
	// node2->freq = tmp_freq;

	// // MUST REPAIR
}

void sort_list(node_t *head){

	node_t *i, *j;

	for(i=head; i!=NULL; i=i->next){
		for(j=i->next; j!=NULL; j=j->next){
			if(i->freq > j->freq)
				swap_nodes(i, j);
		}
	}
}

void free_list(node_t *head){
	node_t *tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

bool insert_node_first(node_t **head, node_t *node){
	if((*head) == NULL || node == NULL)
		return false;

	node->prev = NULL;

	node->next = *head;

	*head = node;

	return true;
}

bool remove_node_first(node_t **head, node_t **node){
	if((*head) == NULL)
		return false;

	(*node) = (*head);

	(*head) = (*head)->next;

	return true;
}

//////////////////////// END OF LINKED LIST DS //////////////////
///////////////////// Q DS USING LINKED LIST ///////////////////

struct Q_t{
	node_t *head;
	node_t *tail;

	Q_t(){
		head = NULL;
		tail = NULL;
	}

	~Q_t(){
		free_list(head);
	}
};

bool enQ(Q_t* q, char item, node_t *node){

	if(node != NULL){
		if(!insert_node_first(&(q->head), node))
			return false;
		sort_list(q->head);
	}
	else{

		node_t *tmp = find_node(q->head, item);

		if(tmp == NULL){

			if(!insert_first(&(q->head), &(q->tail), item))
				return false;

		}
		else{
			tmp->freq++;
			sort_list(q->head);
		}

	}

	return true;
}

bool deQ(Q_t* q, node_t **node){

	if(q->head == NULL){
		(*node) = NULL;
		return false;
	}

	if(!remove_node_first(&(q->head), node))
		return false;

	return true;
}

///////////////////// END OF Q DS ///////////////////

#endif