#include <stdio.h>
#include <stdlib.h>

int count_char(char c){
	 
}


// Read input FILE and load it to memory
int get_input(const char *file_name){

	FILE *file = fopen(file_name, "r");
	int total_char = 0;
	char c;

	while((c=fgetc(file)) != EOF){
		//how do i count tho...
	}

}