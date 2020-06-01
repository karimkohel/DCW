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

	// encode(tmp3, "", table);
	char *v = "01";
	strcat(v,"1");
	table[((int)'c')] = v;
	table[((int)'e')] = "1010";
	table[((int)'t')] = "1010";
	table[((int)'6')] = "1010";
	table[((int)'8')] = "1010";
	table[((int)'1')] = "1010";
	table[((int)'d')] = "1010";
	table[((int)'b')] = "1010";
	table[((int)'/')] = "1010";

	print_table(table);


    return 0;
}