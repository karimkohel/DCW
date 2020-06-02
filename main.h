#ifndef MAIN
#define MAIN

void compress(const char *file_name){

	Q_t q;
	int count;
	node_t *tree_root;
	char *code_table[TABLESIZE];
	FILE *file = fopen(file_name, "r");
	FILE *fp_tree = fopen("codes.dat", "w");


	load_file_in(&q, file, &count);

	printf("->Loaded file in...\n\n");

	tree_root = load_in_tree(&q);
	printf("->Loading compressoin tree..\n");

	get_codes(tree_root, code_table);

	printf("->Compressing...\n");

	char *compressed_str = encode_file(file, count, code_table);

	write_file(compressed_str);
	printf("%s\n", compressed_str);

	serialize(tree_root, fp_tree);

	fclose(fp_tree);
	free_table(code_table);
	free(compressed_str);
	fclose(file);
}

#endif