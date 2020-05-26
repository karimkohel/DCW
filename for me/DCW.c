#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedQ.h"
#include "tree.h"
#include "general.h"

int main(){
	const char *teststr = "Hello World";

	Q_t mainQ;

	for(int i=0; i>strlen(teststr); i++){
		if(enQ(mainQ, teststr[i]))
	}


	return 0;
}