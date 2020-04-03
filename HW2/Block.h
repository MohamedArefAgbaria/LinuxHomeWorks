#ifndef __BLOCK_H
#define __BLOCK_H

#include<stdio.h>
#include<stdlib.h>
#include<zlib.h>
#include <time.h>
#include <string.h>

#define MINDIFFICULTY 0xffff

typedef struct 
{
    int         height;        // Incrementeal ID of the block in the chain
    int         timestamp;    // Time of the mine in seconds since epoch
    unsigned int     hash;        // Current block hash value
    unsigned int     prev_hash;    // Hash value of the previous block
    int        difficulty;    // Amount of preceding zeros in the hash
    int         nonce;        // Incremental integer to change the hash value
    int         relayed_by;    // Miner ID
} BLOCK_T;

void printBlcokAttributes(BLOCK_T* block);
void createCrc32StringFromBlock(char** crc32String, BLOCK_T* block);
unsigned int getHash(BLOCK_T* block);
int countZeros(unsigned int x);
#endif 
