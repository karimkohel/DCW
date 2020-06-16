#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "errhandling.h"
#include "linkedQ.h"
#include "tree.h"
#include "hashtable.h"
#include "general.h"
#include "main.h"

//				----The Delightful Compression Wizard----
//
// for Usage, documentation, developement and commit history, the github repo
// github.com/karimkohel/DCW should be publically available
// by the time of this review.
//
// NOTICE: 
//	-to build on Visual Studio: the header files should be pointed to in the project properties
//		menu under C/C++ > all options -> additional include directories.
//
//	-and to turn off the extra security checks by adding _CRT_SECURE_NO_WARNINGS into the
//		preprocessor definitions in project > project properties > C/C++ > preprocessor.
//	
// 	-this file should be compiled by a C++ compiler
//
//	-people that i helped and should have credited me in their code:
//		-> nourhan el yamany
//		-> mohamed osama
//		-> aly khaled anas
//		-> omar tamer
//		-> amr mekky
//


int main(int argc, char const *argv[]){

	if(argc == 1){

		int choice = greet();

		if(choice == 1)
			compress("input2.txt", "output.dat");
		else if(choice == 2)
			decompress("output.dat", "decompressed.txt");
		else
			fail("=== Exiting ===");
		
	}
	else if(argc == 4){

		if(!strcmp(argv[1], "-c"))
			compress(argv[2], argv[3]);

		else if(!strcmp(argv[1], "-d"))
			decompress(argv[2], argv[3]);

		else
			help_user();
	}
	else
		help_user();

    return 0;
}