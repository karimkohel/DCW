#ifndef HASHTABLE
#define HASHTABLE

#define TABLESIZE 255

// while thinking that a map is the best solution to store huffman codes with a O(1) acces time
// as the app must acces the codes so much and time is of the essence.
// i found out that i don't have to implement a hash function for my table, i can just use the ascii
// table indices instead of hashing my own. what a nifty little hack.

void init_table(char *table[]){

	for(int i=0; i<TABLESIZE; i++){
		table[i] = NULL;
	}
}

void print_table(char *table[]){
	for(int i=0; i<TABLESIZE; i++){
		if(table[i])
			printf("%d - %s - %c\n", i, table[i], i);
	}
}

void free_table(char *table[]){
	for(int i=0; i<TABLESIZE; i++){
		if(table[i])
			free(table[i]);
	}
}

#endif