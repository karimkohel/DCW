#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedQ.h"
#include "tree.h"
#include "hashtable.h"
#include "general.h"
#include "main.h"

int main(){

	greet();

	// bool wanna_compress = get_input();

	if(false)
		compress("input2.txt");
	else{
		FILE *tree_file = fopen("codes.dat", "rb");
		FILE *in_file = fopen("output.txt", "r");
		FILE *out_file = fopen("Decompressed.txt", "w");

		node_t tree_root;
		deserialize(&tree_root, tree_file);
		fclose(tree_file);

		decode(tree_root, in_file, out_file, tree_root->freq);
		fclose(in_file);




		// free_tree(&tree_root);
	}

    return 0;
}