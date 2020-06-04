#ifndef GENERAL
#define GENERAL

void greet(){
	printf("\n===== Hello and welcome to the DCW =====\n\n");
	printf("What do you need to do today?\n");
	printf("-1- Compress\n");
	printf("-2- Decompress\n");
	printf("$ ");
}

bool get_input(){
	int i;

	do{
		scanf("%d", &i);
	}
	while(i != 1 && i != 2);

	if(i == 1) return true;
	else return false;
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
	// the default strcat was causing some problems that i did't feel like looking into so i made my own
	// (it's WET code i know but i don't do that much often)
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

void encode_tree(node_t *node, char code[], char *codes_table[]){
	if(node == NULL)
		return; // base case for children of leaf nodes

	if(leaf_node(node))
		codes_table[((int)node->data)] = code;


	encode_tree(node->left, strcat2(code, "0"), codes_table);
	encode_tree(node->right, strcat2(code, "1"), codes_table);
}

void get_codes(node_t *root, char *table[]){

	init_table(table);

	char tmp_code[50] = "";
	encode_tree(root, tmp_code, table);

	// print_table(table);
}

node_t *load_in_tree(Q_t *q){

	node_t *tmp_node1;
	node_t *tmp_node2;
	node_t *joined_node;

	while(deQ(q, &tmp_node1) && deQ(q, &tmp_node2)){
		joined_node = join_nodes(tmp_node1, tmp_node2);
		enQ(q, '\0', joined_node);
	}
	return joined_node;
}

char *encode_file(FILE *file, int count, char *table[]){

	fseek(file, 0, SEEK_SET); //(CRDTS)//got the seek function from tutorialspoint.com

	char c;
	char *str = (char *)malloc(sizeof(char)*count*10);
	int intc;
	while((c=fgetc(file)) != EOF){
		intc = (int)c;
		strcat(str, table[intc]);
	}
	printf("\n%s\n", str);
	return str;
}

void write_file(char *str){
	FILE *fp = fopen("output.txt", "w");
	char tmp[8];
	int len = strlen(str);
	char c;
	for(int i=0; i<(len/8); i++){
		strncpy(tmp, str, 8);
		c = strtol(tmp, 0,2);
		str = str + 8; //i love pointer arithmatics
		fputc(c, fp);
	}
	fputc('\0', fp);
	fclose(fp);
}

void serialize(node_t *root, FILE *file){
	//(CRDTS)//got the function recursive idea from geeksforgeeks.org
	// but was edited heavily
 
    if (root == NULL){ 
        // fwrite(root, sizeof(node_t), 1, file); need to come back to this
        return; 
    } 
  
    fwrite(root, sizeof(node_t), 1, file); 
    serialize(root->left, file); 
    serialize(root->right, file);
}

void deserialize(node_t *root, FILE *file) {
	//(CRDTS)//got the function recursive idea from geeksforgeeks.org
	// but was edited heavily
	fread(root, sizeof(node_t), 1, file);

	if(leaf_node(root))
		return;

	root->left = (node_t *)malloc(sizeof(node_t));
	root->right = (node_t *)malloc(sizeof(node_t));
	deserialize(root->left, file); 
	deserialize(root->right, file); 
}

void atob(char* buffer, int n){
	//(CRDTS)//got the function idea from programmingsimplified.org
	// had to learn about binary operators and shifting bits,
	// bitwise and all around to pull this off
	// the awesome name i gave this function however is 100% mine
	int c, k; 
    for (c = 7; c >= 0; c--){
	    k = n >> c;

	    if (k & 1)
	      strcat(buffer, "1");
	    else
	      strcat(buffer, "0");
    }
}

char *get_bits(node_t *tree, FILE *compressed_file, int comp_file_size, int tree_hight){

	char c;
	char *bits = (char *)malloc(sizeof(char)*comp_file_size*tree_hight);
	char buffer[9];
	int counter = 0;

	bits[0] = '\0'; //for some reason the new string start off with garbage value?
	while(!feof(compressed_file)){
		c=fgetc(compressed_file);
		atob(buffer, c);
		strcat(bits, buffer);
		buffer[0] = '\0';
		counter++;
		//pass hena cuz loop exits magically
	}
	printf("count = %d\n", counter);

	return bits;
}

void decode_and_write(node_t *root, char *bits, FILE *out_file){

	int len = strlen(bits); //because strlen returns a size_t type i put it in an int
	node_t *tmp = root;
	for(int i=0; i<len; i++){

		if(bits[i] == '0')
			tmp = tmp->left;
		else
			tmp = tmp->right;
		
		if(leaf_node(tmp)){
			fputc(tmp->data, out_file);
			tmp = root;
		}
	}
}

float get_ratio(int in_file_count, int out_file_count){
	float result = (float)out_file_count/in_file_count;
	result = result * 100;
	return result;
}

#endif