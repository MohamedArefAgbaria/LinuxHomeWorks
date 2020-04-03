#include "lib.h"
#include "lib.c"
#include"Ex3Miner.h"

void setMinerData(MINER_T* newMiner,char* cmd_Arg);
void setMinerMessageQueueattributes(struct mq_attr *MMQAttributes);
void sendConnectionRequest(MINER_T* miner);
void waitForServerListening(mqd_t minerMessageQueue);
BLOCK_T getInitialBlockFromServer(mqd_t minerMessageQueue, int minerId);
void listenToTheVerificatedBlocks(mqd_t minerMessageQueue, int MinerId,BLOCK_T* block);
void generateNextBlock(BLOCK_T* block, MINER_T* miner, int* nonce);

void setMinerMessageQueueattributes(struct mq_attr *MMQAttributes)
{
	MMQAttributes->mq_maxmsg = MQ_MAX_SIZE;
	MMQAttributes->mq_msgsize = MQ_MAX_MSG_SIZE;
}

void setMinerData(MINER_T* newMiner,char* cmd_Arg)
{
	sscanf(cmd_Arg,"%d",&newMiner->id);
	strcpy(newMiner->name,MINER_MQ_NAME);
	strcat(newMiner->name,cmd_Arg);
	struct mq_attr mqAttr = { 0 };
	setMinerMessageQueueattributes(&mqAttr);
	unlink(newMiner->name);
	newMiner->messageQueue = mq_open(newMiner->name, O_CREAT | O_RDONLY, S_IRWXU | S_IRWXG, &mqAttr);
	newMiner->serverPartnerMessageQueue = mq_open(SERVER_MQ_NAME, O_WRONLY);
	printf("Miner Id = %d queue name = %s\n",newMiner->id, newMiner->name);
}

void sendConnectionRequest(MINER_T* miner)
{
	BLOCK_T block= { 0,miner->id,0,0,0,0,0 };
	if (mq_send(miner->serverPartnerMessageQueue, (char*)&block, MQ_MAX_MSG_SIZE, 0) == -1)
	{
		printf("Failed Connection to Server\nRun server first!\n");
		exit(0);
	}
	printf("Miner %d sent connect request on %s\n", miner->id, miner->name);
}


void waitForServerListening(mqd_t minerMessageQueue)
{
	struct mq_attr mqAttr = { 0 };
	while (mqAttr.mq_curmsgs == 0)
	{
		mq_getattr(minerMessageQueue, &mqAttr);
	}
}

BLOCK_T getInitialBlockFromServer(mqd_t minerMessageQueue,int minerId)
{
	BLOCK_T initialBlock;
		mq_receive(minerMessageQueue, (char*)&initialBlock, MQ_MAX_MSG_SIZE, NULL);
	printf("Miner #%d received first block: relayed by(%d), ",minerId, initialBlock.relayed_by);
	printBlcokAttributes(&initialBlock);
	return initialBlock;
}

void listenToTheVerificatedBlocks(mqd_t minerMessageQueue, int MinerId,BLOCK_T* block)
{
		struct mq_attr mqAttr = { 0 };
		mq_getattr(minerMessageQueue, &mqAttr);
		while (mqAttr.mq_curmsgs > 0)
		{
			mq_receive(minerMessageQueue, (char*)block, MQ_MAX_MSG_SIZE, NULL);
			printf("Miner #%d received block: relayed by(%d), ",MinerId, block->relayed_by);
			printBlcokAttributes(block);
			mq_getattr(minerMessageQueue, &mqAttr);	
		}
}

void generateNextBlock(BLOCK_T* block,MINER_T* miner,int* nonce)
{
		time_t seconds = time(NULL);
		char buffer[100];
		BLOCK_T newBlock = { block->height+1,seconds,0,block->hash,block->difficulty,(*nonce)++,miner->id };
		blockToString(newBlock, buffer);
		int hash = crc32(0, buffer, strlen(buffer));
		int numOfZeros = countSetBits(hash, newBlock.difficulty);
		if (BLOCKDIFFICULTY <= numOfZeros)
		{
			newBlock.hash = hash;
			struct mq_attr mqAttr = { 0 };
			mq_getattr(miner->serverPartnerMessageQueue, &mqAttr);
			if(mqAttr.mq_curmsgs>=MQ_MAX_SIZE-1)
			{
				printf("miner%d terminated\n",miner->id);
				exit(0);
			}
			printf("Miner#%d mined a new block #%d with the hash 0x%x\n", miner->id, newBlock.height, hash);
			mq_send(miner->serverPartnerMessageQueue, (char*)&newBlock, MQ_MAX_MSG_SIZE, 0);
			*nonce = 0;
		}
}

int main(int argc, char* argv[])
{
	MINER_T new_miner;
	setMinerData(&new_miner,argv[1]);
	sendConnectionRequest(&new_miner);
	waitForServerListening(new_miner.messageQueue);
	BLOCK_T block= { 0,0,0,0,0,0,0 };
	block = getInitialBlockFromServer(new_miner.messageQueue,new_miner.id);
	int nonce = 0;
	for (;;)
	{
		listenToTheVerificatedBlocks(new_miner.messageQueue, new_miner.id,&block);
		generateNextBlock(&block,&new_miner,&nonce);
	}
	return 0;
}
