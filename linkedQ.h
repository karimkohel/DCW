#ifndef linkedQ_H
#define linkedQ_H

typedef struct Node{
	int value;
	Node* next;
};

Node* insertLast(Node* l, int item);
Node* insertFirst(Node* l, int item);
Node* removeLast(Node* l, int* item);
Node* removeFirst(Node* l, int* item);
Node* find(Node* l, int item);
Node* remove(Node* l, int item, bool* status);

typedef struct Queue{
	Node* base;
	Queue(){
		base = NULL;
	}
};

bool enqueue(Queue* s, int item);
bool dequeue(Queue* s, int* item);



#endif