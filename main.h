#ifndef MAIN
#define MAIN

void compress(const char *in_file_name, const char *out_file_name){

	Q_t q;
	FILE *in_file = fopen(in_file_name, "r");
	FILE *codes_file = fopen("codes.dat", "wb");
	FILE *out_file = fopen(out_file_name, "w");

	check_files(in_file, codes_file);

	printf("->Loaded in file...\n");

	int count;
	load_file_in(&q, in_file, &count);

	node_t *tree_root;
	tree_root = load_in_tree(&q);

	printf("->Loading compressoin tree..\n");

	char *code_table[TABLESIZE];
	get_codes(tree_root, code_table);

	printf("->Compressing...\n");

	int tree_hight = find_hight(tree_root);

	encode_file(in_file, code_table, tree_hight, out_file);

	// write_file(compressed_str, out_file_name);//testing the other equivilant function

	serialize(tree_root, codes_file);

	printf("->All Done.\n");

	fclose(codes_file);
	fclose(out_file);
	free_table(code_table);
	// free(compressed_str);
	fclose(in_file);
}

void decompress(const char *comp_file_name, const char *decom_file_name){

	printf("->Loading in files...\n");

	FILE *tree_file = fopen("codes.dat", "rb");
	FILE *in_file = fopen(comp_file_name, "r");
	FILE *out_file = fopen(decom_file_name, "w");

	node_t tree_root;

	deserialize(&tree_root, tree_file);
	fclose(tree_file);

	printf("->Loading metadata...\n");

	int tree_hight = find_hight(&tree_root);

	char *bits = get_bits(&tree_root, in_file, tree_root.freq, tree_hight);
	fclose(in_file);

	printf("->Decompressing...\n");

	decode_and_write(&tree_root, bits, out_file);
	fclose(out_file);

	printf("->All done.\n");

	free(bits);
}


#endif