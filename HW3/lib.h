#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include "zlib.h"
#include"Block.h"

void blockToString(BLOCK_T block, char buffer[100]);
unsigned int countSetBits(unsigned int hsah, int difficulty);
void printBlcokAttributes(BLOCK_T* block);

