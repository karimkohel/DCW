#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "linkedQ.h"
#include "tree.h"
#include "general.h"


int main(){

	Q_t mainQ;
	int count;
	node_t *tmp1;
	node_t *tmp2;
	node_t *tmp3;

	load_file_in(&mainQ, "input2.txt", &count);
	printf("%d bits\n", count*8);

	while(deQ(&mainQ, &tmp1) && deQ(&mainQ, &tmp2)){
		tmp3 = join_nodes(tmp1, tmp2);
		enQ(&mainQ, '\0', tmp3);
	}
	printPostorder(tmp3);
	printf("\n");

	char *table[TABLESIZE];
	init_table(table);

	

	print_table(table);


    return 0;
}