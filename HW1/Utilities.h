#define _CRT_SECURE_NO_WARNINGS
#ifndef __UTILITIES_H
#define __UTILITIES_H
#define BLOCKSDB "blocksdb.txt"
#define CSVFILE "blocksdb.csv"

#include"Block.h"
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

int getHowManyBlocksInTheFile();
Block** loadBlocksFromFile(int howManyBlocksToLoad);
void printOneBlock(Block *block);
void freeBlocks(Block**, int numberOfBlocks);

#endif
