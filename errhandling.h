#ifndef ERRHANDLING
#define ERRHANDLING 

void fail(const char *msg){
	printf("%s\n", msg);
	exit(0);
}

void fcheck(FILE *file, int scenario){
	if(file == NULL){
		if(scenario == 1)
			fail("{ERROR}: Input File not Found");
		else if(scenario == 2)
			fail("{ERROR}: No enough memory in this directory");
		else if(scenario == 3)
			fail("{ERROR}: Compression metadeta not found in directory : codes.dat");
	}
}

void help_user(){
	printf("\n");
	printf("\t\tDCW 1.1\n");
	printf("Usage : DCW <option> <input filename> <output filename>\n");
	printf("\n");
	printf("OPTIONS:\n");
	printf("  -c\tCompress a given text file\n");
	printf("  -d\tDecompress a given compressed file\n");
	printf("EXAMPLES:\n");
	printf("  DCW -c Speach.txt speech.dat\n");
	printf("  DCW -d compressed_Speach.dat speech.txt\n");
	printf("  DCW\n");
	printf("NOTES:\n");
	printf("  Using the tool with no arguments will default to compressing a input.txt file in the same directory\n");
	printf("  Github link: github.com/karimkohel/DCW\n");
	printf("  Make sure to check it out, star the repo and report any bugs if found\n");
	printf("  Documentation at github.com/karimkohel/DCW/DOCUMENTATION\n");
	printf("\n");
	exit(0);
}

#endif