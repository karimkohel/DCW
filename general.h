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

void encode(node_t *node, char code[], char *codes_table[]){
	if(node == NULL)
		return; // base case for children of leaf nodes

	if(leaf_node(node))
		codes_table[((int)node->data)] = code;

	char *code2 = code;
	encode(node->right, strcat(code, "1"), codes_table);
	encode(node->left, strcat(code2, "0"), codes_table);
}

//function that is responsible for getting all huffman codes from a huffman tree
// this function will be documented as it won't be self explanatory enough (because it's probably ugly)
// sorry for the spaghetti code
// bool get_codes(char *codes_table[], node_t *tree){

// 	encode(tree, "",codes_table);
// 	return true;
// }


#endif