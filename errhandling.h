#ifndef ERRHANDLING
#define ERRHANDLING 


void fail(const char *msg){
	printf("%s\n", msg);
	exit(0);
}

void check_files(FILE *in_file, FILE *out_file){
	if(in_file == NULL)
		fail("{ERROR}: Input File not Found");

	if(out_file == NULL)
		fail("{ERROR}: Not enough memory to handle the app");
}

#endif