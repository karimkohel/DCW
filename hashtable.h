#ifndef HASHTABLE
#define HASHTABLE

#define TABLESIZE 256

void init_table(char *table[]){

	for(int i=0; i<TABLESIZE; i++){
		table[i] = NULL;
	}
}

void print_table(char *table[]){
	for(int i=0; i<TABLESIZE; i++){
		if(!table[i])
			printf("%d - \n", i);
		else
			printf("%d - %s\n", i, table[i]);
	}
}

void get_codes(node_t *root, char *table[]){
	
	init_table(table);

	char tmp_code[50] = "";
	encode(root, tmp_code, table);

	print_table(table);
}

#endif