#ifndef HASHTABLE
#define HASHTABLE

#define TABLESIZE 150

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

#endif