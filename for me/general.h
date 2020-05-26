#ifndef GENERAL
#define GENERAL 

void load_file_in(Q_t *q, const char *file_name){

	FILE *file = fopen(file_name, "r");

	char c;
	while((c=fgetc(file)) != EOF){
		if(!enQ(q, c)){
			printf("Error in EnQing\n");
			break;
		}
	}

	fclose(file);
}


#endif