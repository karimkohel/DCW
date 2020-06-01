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


void encode(node_t *tree, node_t **head, node_t **tail, char code[]){

	if(!tree)
		return; // exit case for the nodes after the leafnodes

	if(leaf_node(tree)){
		insert_first(head, tail, )
	}
}

//function that is responsible for getting all huffman codes from a huffman tree
// this function will be documented as it won't be self explanatory enough (because it's probably ugly)
// sorry for the spaghetti code
bool get_codes(node_t **head, node_t *tree){

	if((*head) != NULL)
		return false; // we need an empty list to start

	node_t *tmp_head = NULL;
	node_t *tmp_tail = NULL;

	encode(tree, (&tmp), (&tmp_tail), str);

}


#endif