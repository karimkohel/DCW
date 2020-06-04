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

void help_user(){
	printf("\n");
	printf("\t\tDCW 1.1\n");
	printf("Usage : DCW <option> <filename>\n");
	printf("\n");
	printf("Options:\n");
	printf("  -c\tCompress a given text file\n");
	printf("  -d\tDecompress a given compressed file\n");
	printf("\n");
	exit(0);
}

#endif