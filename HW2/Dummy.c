#include"Dummy.h"
void* dummyMinner()
{
	BLOCK_T newBlock;
	for(;;)
	{
		pthread_mutex_lock(&globalBlockMutex);
		newBlock.prev_hash = 0;
		newBlock.nonce = 0;
		newBlock.height = height;
		newBlock.timestamp = 0;
		newBlock.relayed_by = 5;
		newBlock.hash = 0; 
		newBlock.difficulty = 0;
		printf("Minner #%d: Mined a new block #%d, With hash %x\n",
		newBlock.relayed_by,newBlock.height, newBlock.hash);
		globalBlock = newBlock;
		pthread_cond_signal(&successfully_mined_block_COND);
		pthread_cond_wait(&new_block_verified,&globalBlockMutex);
		pthread_mutex_unlock(&globalBlockMutex);
		sleep(DUMMYTHREADRATE);
	}
	pthread_exit(NULL);
}