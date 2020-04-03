#ifndef __EX3MINER_H
#define __EX3MINER_H
#include"Defines.h"

typedef struct 
{
    int id;
    char name[20];
    mqd_t messageQueue;
    mqd_t serverPartnerMessageQueue;
} MINER_T;

void setMinerData(MINER_T* newMiner,char* cmd_Arg);
void setMinerMessageQueueattributes(struct mq_attr *MMQAttributes);
void sendConnectionRequest(MINER_T* miner);
void waitForServerListening(mqd_t minerMessageQueue);
BLOCK_T getInitialBlockFromServer(mqd_t minerMessageQueue, int MinerId);
void listenToTheVerificatedBlocks(mqd_t minerMessageQueue, int MinerId,BLOCK_T* block);
void generateNextBlock(BLOCK_T* block, MINER_T* miner, int* nonce);

#endif