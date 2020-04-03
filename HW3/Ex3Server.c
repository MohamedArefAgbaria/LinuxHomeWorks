#include "lib.h"
#include "lib.c"
#include "Defines.h"
#include "Ex3Server.h"

void setServerData(SERVER_T* newServer, char* serverName);
void setServerMessageQueueattributes(struct mq_attr *MMQAttributes);
int checkIfConectionRequest(BLOCK_T *block);
void sendFristBlockToMiner(int minerId,BLOCK_T* block, SERVER_T* server);
void checkBlockValidation(BLOCK_T* block,  BLOCK_T* currentBlock, SERVER_T* server);

void setServerData(SERVER_T* server, char* serverName)
{
	server->numberOfBlocks = 0;
	printf("Listening on %s\n",SERVER_MQ_NAME);
	server->Blocks = createLinkedList();
	server->minersNumber = 0;
	strcpy(server->name,serverName);
	struct mq_attr mqAttr = { 0 };
	setServerMessageQueueattributes(&mqAttr);
	mq_unlink(server->name);
	server->messageQueue = mq_open(server->name, O_CREAT | O_RDONLY, S_IRWXU | S_IRWXG, &mqAttr);
}

void setServerMessageQueueattributes(struct mq_attr *MMQAttributes)
{
	MMQAttributes->mq_maxmsg = MQ_MAX_SIZE;
	MMQAttributes->mq_msgsize = MQ_MAX_MSG_SIZE;
}

int isConectionRequest(BLOCK_T *block)
{
	return(!block->hash);
}

void sendFristBlockToMiner(int minerId,BLOCK_T* currentBlock, SERVER_T* server)
{
	char minerName[20] ;
	server->minersNumber++;
	sprintf(minerName,"%s%d",MINER_MQ_NAME,minerId);
	server->minersMessageQueue[server->minersNumber] = mq_open(minerName, O_WRONLY);
	printf("Recieved connection request from miner id %d, queue name: %s\n", minerId, minerName);
	mq_send(server->minersMessageQueue[server->minersNumber], (char*)currentBlock, MQ_MAX_MSG_SIZE, 0);
}

void checkBlockValidation(BLOCK_T* block,  BLOCK_T* currentBlock, SERVER_T* server)
{
	char str[100];
	struct mq_attr attr = { 0 };
	blockToString(*block, str);
	int outcome = crc32(0, str, strlen(str));
	if (block->height != currentBlock->height+1)
		printf("Error:Wrong height for block#%d, recieved %d but the correct height supposed to be: %d\n", currentBlock->height+1, block->height, currentBlock->height + 1);
	else
	{
		if (block->hash == outcome)
		{
			printf("Server:New block added by %d, ", block->relayed_by);
			printBlcokAttributes(block);
			*currentBlock = *block ;
			addNode(&server->Blocks,*block);
			server->numberOfBlocks++;
			for (int i = 1; i <= server->minersNumber; i++)
			{
				mq_getattr(server->minersMessageQueue[i], &attr);
				if(attr.mq_curmsgs<MQ_MAX_SIZE-1)
				{
					mq_send(server->minersMessageQueue[i], (char*)block, MQ_MAX_MSG_SIZE, 0);
				}
			}
		}
		else
		{
			printf("Error:Wrong hash for block#%d, recieved %x but calculated %x\n", block->height, block->hash, outcome);
		}
	}
}

int main()
{
	SERVER_T newServer;
	setServerData(&newServer, SERVER_MQ_NAME);
	BLOCK_T currentBlock = { 0,0,0,0,BLOCKDIFFICULTY,0,0 };
	BLOCK_T block;	
	while(newServer.numberOfBlocks < NUMBEROFBLOCKS)
	{
		mq_receive(newServer.messageQueue, (char*)&block, MQ_MAX_MSG_SIZE, NULL);
		if(isConectionRequest(&block))
		{
			sendFristBlockToMiner(block.timestamp,&currentBlock,&newServer);
		}
		else if (newServer.minersNumber)
		{	
			checkBlockValidation(&block,&currentBlock,&newServer);
		}
	}
	//printLinkedList(&newServer.Blocks); you can print the Blocks
	freeLinkedList(&newServer.Blocks);
	return 0;
}

