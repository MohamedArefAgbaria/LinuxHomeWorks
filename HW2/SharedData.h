#ifndef __SHAREDDATA_H
#define __SHAREDDATA_H

#include<pthread.h>
#include"LinkedList.h"

#define MINERSNUMBER 4
#define MAXNUMBEROFBLOCKS 200
#define DUMMYTHREADRATE 1

int height;
LinkedList BlockChain;
BLOCK_T globalBlock;
pthread_mutex_t globalBlockMutex ;
pthread_mutex_t initialBlockMutex ;
pthread_cond_t new_block_verified ;
pthread_cond_t g_initialBlock_not_empty;
pthread_cond_t successfully_mined_block_COND	;

#endif
