#ifndef linkedQ_H
#define linkedQ_H

//////////////////////// LINKED LIST DS ////////////////////

typedef struct node_t {
	char data;
	int freq;
	node_t *next;
	node_t *prev;
	node_t *left;
	node_t *right;
	// a frankenstein structure
}node_t;

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

void swap_nodes(node_t *node1, node_t *node2){

	if(node1 == node2)
		return;

	char tmp_data = node1->data;
	int tmp_freq = node1->freq;
	node_t *right_tmp = node1->right;
	node_t *left_tmp = node1->left;

	 node1->data = node2->data;
	 node1->freq = node2->freq;
	 node1->left = node2->left;
	 node1->right = node2->right;

	 node2->data = tmp_data;
	 node2->freq = tmp_freq;
	 node2->left = left_tmp;
	 node2->right = right_tmp;
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

typedef struct Q_t{
	node_t *head;
	node_t *tail;

	Q_t(){
		head = NULL;
		tail = NULL;
	}

	~Q_t(){
		// free_list(head);
	}
}Q_t;

bool enQ(Q_t* q, char item, node_t *node){

	// this enQ function is multi-purpose, used to enQ a character and a node
	// by accepting both, it can act according to the input parameters
	// if the input node is null, this means we want to enQ a character
	// else, enQ the node given

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