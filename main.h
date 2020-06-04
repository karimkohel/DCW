#ifndef MAIN
#define MAIN

void compress(const char *file_name){

	Q_t q;
	int count;
	node_t *tree_root;
	char *code_table[TABLESIZE];
	FILE *in_file = fopen(file_name, "r");
	FILE *codes_file = fopen("codes.dat", "wb");

	check_files(in_file, codes_file);

	load_file_in(&q, in_file, &count);

	printf("->Loaded file in...\n");

	tree_root = load_in_tree(&q);
	printf("->Loading compressoin tree..\n");

	get_codes(tree_root, code_table);

	printf("->Compressing...\n");

	int tree_hight = find_hight(tree_root);

	char *compressed_str = encode_file(in_file, count, code_table, tree_hight);

	write_file(compressed_str);

	serialize(tree_root, codes_file);

	printf("->All Done.\n");

	fclose(codes_file);
	free_table(code_table);
	free(compressed_str);
	fclose(in_file);
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