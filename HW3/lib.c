#include"lib.h"

void blockToString(BLOCK_T block, char buffer[100]);
unsigned int countSetBits(unsigned int hsah, int difficulty);
void printBlcokAttributes(BLOCK_T* block);

void printBlcokAttributes(BLOCK_T* block)
{
    printf("height(%d), timestamp(%d), hash(0x%x), prev_hash(0x%x), difficulty(%d), nonce(%d)\n",
    block->height, block->timestamp, block->hash, block->prev_hash, block->difficulty, block->nonce);
}

void blockToString(BLOCK_T block, char buffer[100])
{
	snprintf(buffer, 100, "%d%d%d%x%d", block.timestamp, block.height, block.nonce, block.prev_hash, block.relayed_by);
	
}

unsigned int countSetBits(unsigned int hash, int difficulty)
{
	unsigned int count = 0;
	for (int i = 0; i < (32 - difficulty); i++)
	{
		hash >>= 1;
	}
	while (hash) {
		count += hash & 1;
		hash >>= 1;
	}
	return difficulty - count;
}
