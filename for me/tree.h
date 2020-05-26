#ifndef TREE
#define TREE

struct treeNode_t{
	
	char data;
	int freq;
	treeNode_t *right;
	treeNode_t *left;
};

// adjust bellow for huffman

treeNode_t *createNode(char data){
	treeNode_t *tmp = (treeNode_t *)malloc(sizeof(treeNode_t));
	if(tmp == NULL)
		return NULL;
	tmp->data = data;
	tmp->right = NULL;
	tmp->left = NULL;
	return tmp;
}

treeNode_t *insert(treeNode_t *root, char data){

	if(root == NULL){
		root = createNode(data);
		return root;
	}

	if(data > (root->data))
		root->right = insert(root->right, data);
	else if(data < (root->data))
		root->left = insert(root->left, data);

	return root;
}

treeNode_t *find(treeNode_t *root, char data){

	if(root == NULL)
		return NULL;

	if(data > (root->data))
		return find(root->right, data);
	else if(data < (root->data))
		return find(root->left, data);
	else
		return root;
}

treeNode_t *findMax(treeNode_t *root){

	if(root == NULL)
		return NULL;

	if(root->right)
		return findMax(root->right);
	else
		return root;
}

treeNode_t *findMin(treeNode_t *root){
	if(root == NULL)
		return NULL;

	if(root->left)
		return findMax(root->left);
	else
		return root;
}

bool leefNode(treeNode_t *node){
	if((node->right) == NULL && (node->left) == NULL)
		return true;
	else
		return false;
}

treeNode_t *deleteNode(treeNode_t *node, char data){

	if(node == NULL)
		return NULL;

	if(data > (node->data))
		node->right = deleteNode(node->right, data);
	else if(data < (node->data))
		node->left = deleteNode(node->left, data);
	else{

		if(leefNode(node)){
			free(node);
			node = NULL;
			return node;
		}
		else if((node->left) == NULL){
			treeNode_t *tmp = node;
			node = node->right;
			free(tmp);
		}
		else if((node->right) == NULL){
			treeNode_t *tmp = node;
			node = node->left;
			free(tmp);
		}
		else{
			treeNode_t *tmp = findMin(node->right);//or findMax in left Sub-tree
			node->data = tmp->data;
			node->right = deleteNode(node->right, tmp->data);//to remove duplicate
		}
	}

	return node;
}

#endif 
