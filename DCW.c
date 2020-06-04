#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errhandling.h"
#include "linkedQ.h"
#include "tree.h"
#include "hashtable.h"
#include "general.h"
#include "main.h"

int main(){

	greet();

	bool wanna_compress = get_input();

	if(wanna_compress){

		compress("input.txt");

	}
	else{

		decompress();

	}

    return 0;
}