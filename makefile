all:
	gcc DCW.c linkedQ.c tree.c -o main -g -Wall && ./main

clean:
	rm -f main