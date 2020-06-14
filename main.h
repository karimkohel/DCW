#ifndef MAIN
#define MAIN

void compress(const char *in_file_name, const char *out_file_name){

	clock_t start_time = clock();

	Q_t q;
	FILE *in_file = fopen(in_file_name, "rb");
	fcheck(in_file, 1);
	FILE *codes_file = fopen("codes.dat", "wb");
	fcheck(codes_file, 2);
	FILE *out_file = fopen(out_file_name, "wb");
	fcheck(codes_file, 2);

	printf("->Loading in file...\n");

	long in_count;
	load_file_in(&q, in_file, &in_count);

	node_t *tree_root;
	tree_root = load_in_tree(&q);

	printf("->Loading compressoin data...\n");

	char *code_table[TABLESIZE];
	get_codes(tree_root, code_table);

	printf("->Compressing...\n");

	int tree_hight = find_hight(tree_root);

	char *extra_bits;
	int out_count = encode_file(in_file, code_table, tree_hight, out_file, &extra_bits);

	serialize(tree_root, codes_file);

	write_extra_bits(codes_file, extra_bits);

	printf("->Compressoin Done.\n");
	get_time(start_time);
	printf("== Compressoin ratio = %.2f% ==\n", get_ratio(in_count, out_count));



	free(extra_bits);
	fclose(codes_file);
	fclose(out_file);
	fclose(in_file);
	free_table(code_table);
}

void decompress(const char *comp_file_name, const char *decom_file_name){

	clock_t start_time = clock();

	printf("->Loading in files...\n");

	FILE *codes_file = fopen("codes.dat", "rb");
	fcheck(codes_file, 3);
	FILE *in_file = fopen(comp_file_name, "rb");
	fcheck(in_file, 1);
	FILE *out_file = fopen(decom_file_name, "w");
	fcheck(out_file, 2);

	node_t tree_root;
	char extra_bits[8];

	deserialize(&tree_root, codes_file);
	get_extra_bits(codes_file, extra_bits);
	

	printf("->Loading metadata...\n");

	int tree_hight = find_hight(&tree_root);

	printf("->Decompressing...\n");

	get_bits(&tree_root, in_file, tree_hight, out_file, extra_bits);

	printf("->All done.\n");
	get_time(start_time);

	fclose(codes_file);
	fclose(in_file);
	fclose(out_file);
}

#endif