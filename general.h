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
	int counter = 0;
	int wait = 500000;
	while((c=fgetc(file)) != EOF){
		if(!enQ(q, c, NULL)){
			printf("Error in EnQing\n");
			break;
		}
		if(counter == wait){
			printf("->Still loading...\n");
			wait = wait*2;
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

void trim_str(char *str, int offset){
    int len = strlen(str);
    for(int i=0; i<(len-offset+1); i++){
        str[i] = str[offset+i];
    }
}

int encode_file(FILE *in_file, char *table[], int tree_hight, FILE *comp_file){

	fseek(in_file, 0, SEEK_SET); //(CRDTS)//got the seek function from tutorialspoint.com

	char in_c;
	int out_c;
	char buffer[tree_hight*tree_hight];
	buffer[0] = '\0';
	char tmp[9];
	int len;
	int count = 0;

	while((in_c=fgetc(in_file)) != EOF){

		strcat(buffer, table[((int)in_c)]);
		len = strlen(buffer);

		while(len > 7){
			strncpy(tmp, buffer, 8);
			out_c = strtol(tmp, 0, 2);
			fputc(out_c, comp_file);
			trim_str(buffer, 8);
			len = len - 8;
			count++;
		}
	}

	// len = strlen(buffer);
	// if(len > 0){
	// 	//pass
	// }
	return count;
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

char decode(char *bits, node_t *root, int *offset){ // ad ability to give back offset

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

void get_bits(node_t *root, FILE *comp_file, int tree_h, FILE *out_file){

	char c;
	char bits[tree_h*2];

	char buffer[9];
	int len;
	int offset;

	while(!feof(comp_file)){
		c=fgetc(comp_file);

		atob(buffer, c);

		strcat(bits, buffer);
		len = strlen(bits);

		buffer[0] = '\0';

		while(len > tree_h){
			fputc(decode(bits, root, &offset), out_file);
			len = len - offset;
		}
	}

	if(len > tree_h){
		// pass // the last bits
	}
}

float get_ratio(int in_file_count, int out_file_count){
	float result = (float)out_file_count/in_file_count;
	result = result * 100;
	result = 100 - result;
	return result;
}


#endif