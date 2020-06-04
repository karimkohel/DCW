#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errhandling.h"
#include "linkedQ.h"
#include "tree.h"
#include "hashtable.h"
#include "general.h"
#include "main.h"

int main(int argc, char const *argv[]){

	if(argc == 1){

		greet();

		int choice = get_input();

		if(choice == 1)
			compress("input.txt");
		else if(choice == 2)
			decompress("compressed_input.txt");
		else
			fail("=== Exiting ===");
	}
	else if(argc == 3){
		//pass
	}

    return 0;
}