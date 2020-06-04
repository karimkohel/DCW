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
	printf("OPTIONS:\n");
	printf("  -c\tCompress a given text file\n");
	printf("  -d\tDecompress a given compressed file\n");
	printf("EXAMPLES:\n");
	printf("  DCW -c Speach.txt\n");
	printf("  DCW -d compressed_Speach.txt\n");
	printf("  DCW\n");
	printf("NOTES:\n");
	printf("  Using the tool with no arguments will default to compressing a input.txt file in the same directory\n");
	printf("  Github link: github.com/karimkohel/DCW\n");
	printf("  Make sure to check it out, star the repo and report any bugs if found\n");
	printf("\n");
	exit(0);
}

#endif