#ifndef MAIN
#define MAIN

void compress(const char *file_name){

	Q_t q;
	int count;
	node_t *tree_root;
	char *code_table[TABLESIZE];
	FILE *file = fopen(file_name, "r");
	FILE *fp_tree = fopen("codes.dat", "wb");


	load_file_in(&q, file, &count);

	printf("->Loaded file in...\n");

	tree_root = load_in_tree(&q);
	printf("->Loading compressoin tree..\n");

	get_codes(tree_root, code_table);

	printf("->Compressing...\n");

	char *compressed_str = encode_file(file, count, code_table);

	write_file(compressed_str);

	serialize(tree_root, fp_tree);

	printf("->All Done.\n");

	fclose(fp_tree);
	free_table(code_table);
	free(compressed_str);
	fclose(file);
}

void decompress(){

	printf("->Loading in files...\n");

	FILE *tree_file = fopen("codes.dat", "rb");
	FILE *in_file = fopen("output.txt", "r");
	FILE *out_file = fopen("Decompressed.txt", "w");

	node_t tree_root;

	deserialize(&tree_root, tree_file);
	fclose(tree_file);

	printf("->Loading metadata...\n");

	int tree_hight = find_hight(&tree_root);
	printf("H=%d\n", tree_hight);

	char *bits = get_bits(&tree_root, in_file, tree_root.freq, tree_hight);
	fclose(in_file);

	printf("->Decompressing...\n");

	decode_and_write(&tree_root, bits, out_file);
	fclose(out_file);

	printf("->All done.\n");

	free(bits);
}


#endif