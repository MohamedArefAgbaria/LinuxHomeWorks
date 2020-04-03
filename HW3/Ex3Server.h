#ifndef __EX3SERVER_H
#define __EX3SERVER_H
#include"Defines.h"
#include "LinkedList.h"

typedef struct 
{
    char name[20];
    mqd_t messageQueue;
    mqd_t minersMessageQueue[MAXAMOUNTMINERS];
    int minersNumber;
    LinkedList Blocks;
    int numberOfBlocks;
} SERVER_T;

void setServerData(SERVER_T* newServer,char* serverName);
void setServerMessageQueueattributes(struct mq_attr *MMQAttributes);
int isConectionRequest(BLOCK_T *block);
void sendFristBlockToMiner(int minerId,BLOCK_T* block, SERVER_T* server);
void checkBlockValidation(BLOCK_T* block,  BLOCK_T* currentBlock, SERVER_T* server);

#endif