#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedQ.h"
#include "tree.h"
#include "general.h"
#include "hashtable.h"

int main(){

	Q_t q;
	int count;
	node_t *root;
	char *code_table[TABLESIZE];
	FILE *file = fopen("input.txt", "r");

	load_file_in(&q, file, &count);

	greet();

	printf("Loaded file in\n\n");

	root = load_in_tree(&q);

	get_codes(root, code_table);

	printf("Compressing\n");

	char *compressed = compress(file, count, code_table);

	printf("%s\n", compressed);

	free(compressed);
	fclose(file);
    return 0;
}