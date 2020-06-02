#ifndef GENERAL
#define GENERAL

void greet(){
	printf("\n===== Hello and welcome to the DCW =====\n\n");
}

void load_file_in(Q_t *q, FILE *file, int *count){

	char c;
	int counter = 0;
	while((c=fgetc(file)) != EOF){
		if(!enQ(q, c, NULL)){
			printf("Error in EnQing\n");
			break;
		}
		counter++;
	}

	*count = counter;

}

char *strcat2(char *str1, const char *str2){
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int len3 = len1+len2+1;

	char *str = (char *)malloc(sizeof(char)*len3);
	int i;

	for(i=0; i<len1; i++){
		str[i] = str1[i];
	}
	for(int j=0;j<len2; j++, ++i){
		str[i] = str2[j];
	}
	i++;
	str[i] = '\0';

	return str;
}

void encode(node_t *node, char code[], char *codes_table[]){
	if(node == NULL)
		return; // base case for children of leaf nodes

	if(leaf_node(node))
		codes_table[((int)node->data)] = code;


	encode(node->left, strcat2(code, "0"), codes_table);
	encode(node->right, strcat2(code, "1"), codes_table);
}

node_t *load_in_tree(Q_t *q){

	node_t *tmp_node1;
	node_t *tmp_node2;
	node_t *joined_node;

	while(deQ(q, &tmp_node1) && deQ(q, &tmp_node2)){
		joined_node = join_nodes(tmp_node1, tmp_node2);
		enQ(q, '\0', joined_node);
	}
	printPostorder(joined_node);
	printf("\n");
	return joined_node;
}

char *compress(FILE *file, int count, char *table[]){

	fseek(file, 0, SEEK_SET );

	char c;
	char *str = (char *)malloc(sizeof(char)*count*20);
	int intc;
	while((c=fgetc(file)) != EOF){
		intc = (int)c;
		strcat(str, table[intc]);
	}
	return str;
}

#endif