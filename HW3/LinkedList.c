#include"LinkedList.h"
#include<stdio.h>
#include<stdlib.h>

void printBlcokAttributess(BLOCK_T* block)
{
    printf("height(%d), timestamp(%d), hash(0x%x), prev_hash(0x%x), difficulty(%d), nonce(%d)\n",
    block->height, block->timestamp, block->hash, block->prev_hash, block->difficulty, block->nonce);
}
LinkedList createLinkedList()
{
    LinkedList newLinkedList;
    newLinkedList.head = newLinkedList.tail = NULL;
    return newLinkedList;
}

void addNode(LinkedList* linkedList,BLOCK_T block)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->previous = NULL;
    newNode->next = NULL;
    newNode->data = block;

    if(linkedList->head == NULL)
    {
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    else
    {
        newNode->previous = linkedList->tail;
        linkedList->tail->next = newNode;
        linkedList->tail = newNode;
    }
}

void printLinkedList(LinkedList* linkedList)
{
    Node* currentNode = linkedList->head;
	if (currentNode == NULL)
		printf("Empty BlockChain\n\n");
	while (currentNode != NULL)
	{
		printf("Block details:\n\n");
		printBlcokAttributess(&currentNode->data);
        currentNode = currentNode->next;
	}
}

void freeLinkedList(LinkedList* linkedList)
{
    Node* currentNode = linkedList->head;
	while (currentNode != NULL)
	{
		linkedList->head = currentNode->next;
        free(currentNode);
        currentNode = linkedList->head;
	}
}
