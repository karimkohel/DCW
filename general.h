#ifndef GENERAL
#define GENERAL

int greet(){
	printf("\n===== Hello and welcome to the DCW =====\n\n");
	printf("What do you need to do today?\n");
	printf("-1- Compress\n");
	printf("-2- Decompress\n");
	printf("-3- Exit\n");
	printf("$ ");

	int i;

	do{
		scanf("%d", &i);
	}
	while(i > 3 || i < 1);

	return i;
}

void load_file_in(Q_t *q, FILE *file, int *count){

	char c;
	unsigned long long counter = 0;
	unsigned long long wait = 10000000;
	while(fread(&c, sizeof(char), 1, file) == 1){
		if(!enQ(q, c, NULL)){
			printf("Error in EnQing\n");
			break;
		}
		if(counter == wait && counter < 100000000){
			printf("->Still loading...\n");
			wait = wait + 10000000;
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
	str[0] = '\0';
	int i;

	for(i=0; i<len1; i++){
		str[i] = str1[i];
	}
	for(int j=0;j<len2; j++, ++i){
		str[i] = str2[j];
	}
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
	tmp_code[0] = '\0';
	encode_tree(root, tmp_code, table);

	// print_table(table);
}

node_t *load_in_tree(Q_t *q){

	node_t *tmp_node1 = NULL;
	node_t *tmp_node2 = NULL;
	node_t *joined_node = NULL;

	while(deQ(q, &tmp_node1) && deQ(q, &tmp_node2)){
		joined_node = join_nodes(tmp_node1, tmp_node2);
		enQ(q, '\0', joined_node);
	}
	return joined_node;
}

void trim_str(char *str, int offset){
    int len = strlen(str);
    for(int i=0; i<(len-offset+1); i++){
        str[i] = str[offset+i];
    }
}

int encode_file(FILE *in_file, char *table[], int tree_hight, FILE *comp_file, char **extra_bits){

	fseek(in_file, 0, SEEK_SET); //(CRDTS)//got the seek function from tutorialspoint.com

	char in_c;
	int out_c;
	char out_c2;
	char *buffer = (char *)malloc(tree_hight*tree_hight*sizeof(char));
	buffer[0] = '\0'; // the string starts with garbage value for some reason
	char tmp[9];
	int len;
	int count = 0;

	while(fread(&in_c, sizeof(char), 1, in_file) == 1){

		strcat(buffer, table[((int)in_c)]);
		len = strlen(buffer);

		while(len > 7){
			strncpy(tmp, buffer, 8);
			out_c = strtol(tmp, 0, 2);
			out_c2 = out_c;
			fwrite(&out_c2, sizeof(char), 1, comp_file);
			trim_str(buffer, 8);
			len = len - 8;
			count++;
		}
	}

	*extra_bits = buffer;
	return count;
}

void write_extra_bits(FILE *file, char *bits){
	int len = strlen(bits);
	for(int i=0; i<len+1; i++){
		fwrite(&bits[i], sizeof(char), 1, file);
	}
}

void serialize(node_t *root, FILE *file){
 
    if (root == NULL){ 
        // fwrite(root, sizeof(node_t), 1, file); // need to come back to this
        return; 
    } 
  
    fwrite(root, sizeof(node_t), 1, file); 
    serialize(root->left, file); 
    serialize(root->right, file);
}

void deserialize(node_t *root, FILE *file) {
	fread(root, sizeof(node_t), 1, file);

	if(leaf_node(root))
		return;

	root->left = (node_t *)malloc(sizeof(node_t));
	root->right = (node_t *)malloc(sizeof(node_t));
	deserialize(root->left, file); 
	deserialize(root->right, file); 
}

void get_extra_bits(FILE *file, char *bits){
	for(int i=0; i<8; i++){
		fread(&bits[i], sizeof(char), 1, file);
		if(bits[i] == '\0')
			break;
	}
}

void atob(char* buffer, int c){
	//(CRDTS)//got the function idea from programmingsimplified.org
	// had to learn about binary operators and shifting bits,
	// bitwise and all around to pull this off
	// the awesome name i gave this function however is 100% mine

	int k; 
    for(int i = 7; i >= 0; i--){
	    k = c >> i; // right shift all bits in c by i times (which is equivilant of deviding by 2^*right operand*

	    if (k & 1)//all bits in k AND gated to all bits in 1 (Which are 00000001)
	      strcat(buffer, "1");
	    else
	      strcat(buffer, "0");
    }
}

char decode(char *bits, node_t *root, int *offset){

	int len = strlen(bits);
	int j = 1;
	for(int i=0; i<len; i++, j++){

		if(bits[i] == '0'){
			root = root->left;
		}
		else{
			root = root->right;
		}

		if(leaf_node(root))
			break;
	}

	trim_str(bits, j);

	*offset = j;

	return root->data;
}

void get_bits(node_t *root, FILE *comp_file, int tree_h, FILE *out_file, char *extra_bits){

	char c;
	char out_c;
	char *bits = (char *)malloc(sizeof(char)*tree_h*tree_h);
	bits[0] = '\0';
	char buffer[9];
	buffer[0] = '\0';
	int len;
	int offset;

	while(fread(&c, sizeof(char), 1, comp_file) == 1){

		atob(buffer, c);

		strcat(bits, buffer);

		len = strlen(bits);

		buffer[0] = '\0';

		while(len > tree_h){
			out_c = decode(bits, root, &offset);
			fwrite(&out_c, sizeof(char), 1, out_file);
			len = len - offset;
		}
	}

	strcat(bits, extra_bits);

	while(len > 0){
		out_c = decode(bits, root, &offset);
		fwrite(&out_c, sizeof(char), 1, out_file);
		len = len - offset;
	}
	free(bits);
}

float get_ratio(int in_file_count, int out_file_count){
	float result = (float)out_file_count/in_file_count;
	result = result * 100;
	result = 100 - result;
	return result;
}


#endif