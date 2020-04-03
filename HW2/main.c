#include"Miner.h"
#include"Server.h"
#include"Dummy.h"

void initialGlobalVariables()
{
	int height = 0;
	pthread_mutex_t globalBlockMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t initialBlockMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t new_block_verified	= PTHREAD_COND_INITIALIZER;
	pthread_cond_t g_initialBlock_not_empty	= PTHREAD_COND_INITIALIZER; 
	pthread_cond_t successfully_mined_block_COND	= PTHREAD_COND_INITIALIZER; 
}

void main()
{	

	initialGlobalVariables();
	int* minerThreadsId = (int*)malloc(MINERSNUMBER*sizeof(int));
	pthread_t server_thread;
	pthread_create(&server_thread, NULL, server, NULL); 

	pthread_t* minerThreads = (pthread_t*)malloc(MINERSNUMBER*sizeof(pthread_t)); 
	for (int i = 0 ; i< MINERSNUMBER;i++)
	{
		minerThreadsId[i] = i+1;
		pthread_create(&minerThreads[i],NULL,miner,&minerThreadsId[i]);
	}

	pthread_t dummyMiner_thread;
	pthread_create(&dummyMiner_thread, NULL, dummyMinner, NULL); 

	pthread_join(server_thread,NULL);
	free(minerThreadsId);
	free(minerThreads);
	freeLinkedList(&BlockChain);

}
