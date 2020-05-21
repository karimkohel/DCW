all:
	gcc DCW.c linkedQ.c -o main -g -Wall && ./main

clean:
	rm -f main