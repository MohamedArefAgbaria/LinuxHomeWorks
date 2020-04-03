#include"Utilities.h"

void createCsvFile(Block** blocks, int numberOfBlocks)
{
	FILE* fp = fopen(CSVFILE, "w");
	if (fp == NULL)
	{
		printf("Failed Open File\n");
		return;
	}
	fprintf(fp, "hash,height,total,time,received_time,relayed_by,prev_block");
	for (int i = 0; i < numberOfBlocks; i++) 
	{
		fprintf(fp, "\n%s,%s,%s,%s,%s,%s,%s",blocks[i]->hash, blocks[i]->height, blocks[i]->total
			, blocks[i]->time, blocks[i]->received_time,blocks[i]->relayed_by, blocks[i]->prev_block);
	}
	fclose(fp);
}

int main() {

	int numberOfBlocks = getHowManyBlocksInTheFile();
	Block** blocks = loadBlocksFromFile(numberOfBlocks);
	createCsvFile(blocks,numberOfBlocks);
	freeBlocks(blocks, numberOfBlocks);
	return 0;
}
