#ifndef TREE
#define TREE


bool leaf_node(node_t *node){
	if(node->right == NULL && node->left == NULL)
		return true;
	else 
		return false;

}

node_t *join_nodes(node_t *node1, node_t *node2){

	node_t *new_node = create_node('\0');
	if(new_node == NULL)
		return NULL;

	new_node->left = node1;
	new_node->right = node2;
	new_node->freq = (node1->freq) + (node2->freq);
	new_node->data = '\0';

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

void printPostorder(node_t *root){
	if(root == NULL)
		return;

	printPostorder(root->left);
	printPostorder(root->right);
	if(root->data == '\0')
		printf("(%d)~", root->freq);
	else
		printf("[%c]~", root->data);
}

#endif 
