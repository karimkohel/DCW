#ifndef GENERAL
#define GENERAL

void greet_and_help(){
	printf("===== Hello and welcome to the DCW =====\n\n");
	printf("- Loading in the file\n");
}

void load_file_in(Q_t *q, const char *file_name, int *count){

	FILE *file = fopen(file_name, "r");

	char c;
	int counter = 0;
	while((c=fgetc(file)) != EOF){
		if(!enQ(q, c, NULL)){
			printf("Error in EnQing\n");
			break;
		}
		counter++;
	}

	*count = counter;
	fclose(file);
}

// //plagiarized function do not use
// #include <errno.h>
// #include <string.h>
// #include <sys/stat.h>
// static unsigned get_file_size (const char * file_name){
//     struct stat sb;
//     if (stat (file_name, & sb) != 0) {
//         fprintf (stderr, "'stat' failed for '%s': %s.\n",
//                  file_name, strerror (errno));
//         exit (EXIT_FAILURE);
//     }
//     return sb.st_size;
// }

char *strcat2(char *str1, const char *str2){
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int len3 = len1+len2+1;

	char *str = (char *)malloc(sizeof(char)*len3);
	int i;

	for(i=0; i<len1; i++){
		str[i] = str1[i];
	}
	for(int j=0;j<len2; j++, ++i){
		str[i] = str2[j];
	}
	i++;
	str[i] = '\0';

	return str;
}

void encode(node_t *node, char code[], char *codes_table[]){
	if(node == NULL)
		return; // base case for children of leaf nodes

	if(leaf_node(node))
		codes_table[((int)node->data)] = code;


	encode(node->left, strcat2(code, "0"), codes_table);
	encode(node->right, strcat2(code, "1"), codes_table);
}

//function that is responsible for getting all huffman codes from a huffman tree
// this function will be documented as it won't be self explanatory enough (because it's probably ugly)
// sorry for the spaghetti code
// bool get_codes(char *codes_table[], node_t *tree){

// 	encode(tree, "",codes_table);
// 	return true;
// }


#endif