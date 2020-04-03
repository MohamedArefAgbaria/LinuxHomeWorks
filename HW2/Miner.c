#include"Miner.h"
#include"SharedData.h"

void mineNewBlock(void* minnerId)
{		
	BLOCK_T newBlock;
	char* crc32String = NULL;
	newBlock.prev_hash = BlockChain.tail->data.hash;
	newBlock.nonce = 0;
	newBlock.height = height;
	newBlock.timestamp = (int)time(NULL);
	newBlock.relayed_by = *(int*)minnerId;
	createCrc32StringFromBlock(&crc32String,&newBlock);
	newBlock.hash = getHash(&newBlock); 
	newBlock.difficulty = countZeros(newBlock.hash);
	printf("Miner #%d: Mined a new block #%d, With hash %x\n",
	newBlock.relayed_by,newBlock.height, newBlock.hash);
	globalBlock = newBlock;
	free(crc32String);
}

void* miner(void* minerID)
{	
	if(!BlockChain.head)
	{	
		pthread_mutex_lock(&initialBlockMutex);
		pthread_cond_wait(&g_initialBlock_not_empty,&initialBlockMutex);
		pthread_mutex_unlock(&initialBlockMutex);
	}
	for(;;)
	{	
		pthread_mutex_lock(&globalBlockMutex);
		mineNewBlock(minerID);
		pthread_cond_signal(&successfully_mined_block_COND); // Notify to server about successfully mined block
		pthread_cond_wait(&new_block_verified,&globalBlockMutex);		
		pthread_mutex_unlock(&globalBlockMutex);
	}
	pthread_exit(NULL);
}
