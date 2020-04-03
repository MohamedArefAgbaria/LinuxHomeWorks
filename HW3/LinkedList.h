#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H
#include"Block.h"

typedef struct LinkedListBlockNode {
	BLOCK_T data;
	struct LinkedListBlockNode* previous;
	struct LinkedListBlockNode* next;
}Node;

typedef struct LinkedListBlocks {
	Node* head;
	Node* tail;
}LinkedList;

LinkedList createLinkedList();
void addNode(LinkedList* linkedList,BLOCK_T data);
void printLinkedList(LinkedList* linkedList);
void freeLinkedList(LinkedList* linkedList);
#endif 