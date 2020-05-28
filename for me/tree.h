#ifndef TREE
#define TREE

node_t *insert(node_t *root, char data){

	if(root == NULL){
		root = create_node(data);
		return root;
	}

	if(data > (root->data))
		root->right = insert(root->right, data);
	else if(data < (root->data))
		root->left = insert(root->left, data);

	return root;
}

node_t *find(node_t *root, char data){

	if(root == NULL)
		return NULL;

	if(data > (root->data))
		return find(root->right, data);
	else if(data < (root->data))
		return find(root->left, data);
	else
		return root;
}

node_t *find_max(node_t *root){

	if(root == NULL)
		return NULL;

	if(root->right)
		return find_max(root->right);
	else
		return root;
}

node_t *find_min(node_t *root){
	if(root == NULL)
		return NULL;

	if(root->left)
		return find_max(root->left);
	else
		return root;
}

bool leef_node(node_t *node){
	if((node->right) == NULL && (node->left) == NULL)
		return true;
	else
		return false;
}

node_t *delete_node(node_t *node, char data){

	if(node == NULL)
		return NULL;

	if(data > (node->data))
		node->right = delete_node(node->right, data);
	else if(data < (node->data))
		node->left = delete_node(node->left, data);
	else{

		if(leef_node(node)){
			free(node);
			node = NULL;
			return node;
		}
		else if((node->left) == NULL){
			node_t *tmp = node;
			node = node->right;
			free(tmp);
		}
		else if((node->right) == NULL){
			node_t *tmp = node;
			node = node->left;
			free(tmp);
		}
		else{
			node_t *tmp = find_min(node->right);//or find_max in left Sub-tree
			node->data = tmp->data;
			node->right = delete_node(node->right, tmp->data);//to remove duplicate
		}
	}

	return node;
}

node_t *join_nodes(node_t *node1, node_t *node2){

	node_t *new_node = create_node('\0');
	if(new_node == NULL)
		return NULL;

	new_node->left = node1;
	new_node->right = node2;
	new_node->freq = (node1->freq) + (node2->freq);

	return new_node;
}

void printInorder(node_t *root){
	if(root == NULL)
		return;
	printInorder(root->left);

	if(root->data == '\0')
		printf("%d~", root->freq);
	else
		printf("%c~", root->data);

	printInorder(root->right);
}


#endif 
