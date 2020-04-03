#include"Server.h"

void generateInitialBlock()
{
	char buffer [50];	
	globalBlock.height = 0;
	globalBlock.timestamp = (int)time(NULL);
	globalBlock.prev_hash = 0;
	sprintf(buffer, "%d", globalBlock.timestamp); 
	globalBlock.hash = crc32(0,buffer,strlen(buffer)); 
	globalBlock.difficulty = countZeros(globalBlock.hash);
	globalBlock.nonce = 0;
	globalBlock.relayed_by = 0;
	addNode(&BlockChain,globalBlock); 
	height++;
}

void checkBlockValidation()
{
	char* buffer2;
	createCrc32StringFromBlock(&buffer2,&globalBlock);
	int checkValidHashResult = crc32(0,buffer2,strlen(buffer2));
	if( 
		checkValidHashResult == globalBlock.hash && 
		globalBlock.prev_hash == BlockChain.tail->data.hash && 
		height == BlockChain.tail->data.height+1)
	{
		printf("Server: New block added by %d, attributes: ",globalBlock.relayed_by);
		printBlcokAttributes(&globalBlock);
		addNode(&BlockChain,globalBlock);
		height++;	
	}
	else
	{
		printf("wrong hash for block %d, by miner %d, received %x but calculated %x\n",
		globalBlock.height,globalBlock.relayed_by,globalBlock.hash,checkValidHashResult);
	}
}

void* server(void* arg1)
{
	generateInitialBlock();
	pthread_cond_broadcast(&g_initialBlock_not_empty); // Notfy Miners about the genesis block
	while(height <= MAXNUMBEROFBLOCKS)
	{	
		pthread_cond_wait(&successfully_mined_block_COND,&globalBlockMutex);// Wait for notification from one of the miners about a successfully mined block
		checkBlockValidation();
		pthread_cond_broadcast(&new_block_verified); //Notfy the miners about validation check
	}
	pthread_exit(NULL);	
}