#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedQ.h"
#include "tree.h"
#include "general.h"


int main(){

	Q_t mainQ;
	int count;
	bool state;
	node_t *tmp1;
	node_t *tmp2;
	node_t *tmp3;

	load_file_in(&mainQ, "input.txt", &count);

	while(deQ(&mainQ, &tmp1) && deQ(&mainQ, &tmp2)){
		tmp3 = join_nodes(tmp1, tmp2);
		state = enQ(&mainQ, '\0', tmp3);
		printf("hey %d- %d\n", state, tmp3->freq);
	}
	printInorder(tmp3);

    return 0;
}