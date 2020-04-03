#include"Block.h"

void printBlcokAttributes(BLOCK_T* block)
{
    printf("height(%d), timestamp(%d), hash(0x%x), prev_hash(0x%x), difficulty(%d), nonce(%d)\n",
    block->height, block->timestamp, block->hash, block->prev_hash, block->difficulty, block->nonce);
}

void createCrc32StringFromBlock(char** crc32String, BLOCK_T* block)
{
    char height[50],timestamp[50],prev_hash[50],nonce[50],relayed_by[50]; 
    int size  = 0; 
    size+= sprintf(height, "%d", block->height); 
    size+= sprintf(timestamp, "%d", block->timestamp); 
    size+= sprintf(prev_hash, "%x", block->prev_hash); 
    size+= sprintf(nonce, "%d", block->nonce); 
    size+= sprintf(relayed_by, "%d", block->relayed_by); 
    *(crc32String) = (char*)malloc((size+1)*sizeof(char));
    snprintf(*crc32String, size+1, "%s%s%s%s%s", height,timestamp,prev_hash,nonce,relayed_by);
}

unsigned int getHash(BLOCK_T* block)
{
    unsigned int new_hash = 0xffffffff;
    char* crc32String;
	while(new_hash > MINDIFFICULTY)	 
	{
		block->nonce++;
		block->timestamp = (int)time(NULL);
		createCrc32StringFromBlock(&crc32String,block);
		new_hash = crc32(0,crc32String,strlen(crc32String));
	}
    return new_hash;
}

int countZeros(unsigned int x) 
{ 
    int total_bits = sizeof(x) * 8; 
    int res = 0; 
    while ( !(x & (1 << (total_bits - 1))) ) 
    { 
        x = (x << 1); 
        res++; 
    } 
    return res; 
} 