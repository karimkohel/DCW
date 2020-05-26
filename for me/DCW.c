#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedQ.h"
#include "tree.h"
#include "general.h"

int main(){
	const char *teststr = "Hello World";

	Q_t mainQ;
	int len = strlen(teststr);

	for(int i=0; i<len; i++){
		if(!enQ(&mainQ, teststr[i])){
			printf("enQ error\n");
			break;
		}
	}

	int freq;
	char item;
	while(deQ(&mainQ, &item, &freq)){
		printf("(%c-%d)\n", item, freq);
	}

	printf("Success\n");

	return 0;
}