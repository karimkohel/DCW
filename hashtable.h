#ifndef HASHTABLE
#define HASHTABLE

#define TABLESIZE 255

// while thinking that a map is the best solution to store huffman codes with a O(1) speed
// if found out that i don't have to implement a hash table to acheive that, i can just use the unicode
// values of characters as table indices instead of hashing my own. and i did it just like that

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

void free_table(char *table[]){
	for(int i=0; i<TABLESIZE; i++){
		free(table[i]);
	}
}

#endif