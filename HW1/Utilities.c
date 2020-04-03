#include"Utilities.h"

int getHowManyBlocksInTheFile()
{
	char buffer[1024];
	int numberOfBlocks = 0;
	FILE* fp = fopen(BLOCKSDB, "r");
	if (fp == NULL)
	{
		printf("Failed Open File");
		return;
	}
	else
	{
		while (fscanf(fp, "%s", buffer) != EOF)
		{
			if (strcmp(buffer, "{") == 0)
			{
				numberOfBlocks++;
			}
		}
	}
	fclose(fp);
	return numberOfBlocks;
}

Block** loadBlocksFromFile(int howManyBlocksToLoad)
{
	Block** blocks = malloc(sizeof(Block*) * howManyBlocksToLoad);
	FILE* fp = fopen(BLOCKSDB, "r");
	char buffer[1024];
	int indexOfCurrentBlock = 0;
	if (fp == NULL)
	{
		printf("Failed Read File");
		return;
	}
	else
	{
		if (fp) {
			while (fscanf(fp, "%s", buffer) != EOF)
			{
				blocks[indexOfCurrentBlock] = malloc(sizeof(Block));
				fscanf(fp, "%s", buffer); 
				fscanf(fp, "%s", blocks[indexOfCurrentBlock]->hash);
				fscanf(fp, "%s", buffer);
				fscanf(fp, "%s", blocks[indexOfCurrentBlock]->height);
				fscanf(fp, "%s", buffer);
				fscanf(fp, "%s", blocks[indexOfCurrentBlock]->total);
				fscanf(fp, "%s", buffer);
				fscanf(fp, "%s", blocks[indexOfCurrentBlock]->time);
				fscanf(fp, "%s", buffer);
				fscanf(fp, "%s", blocks[indexOfCurrentBlock]->received_time);
				fscanf(fp, "%s", buffer);
				fscanf(fp, "%s", blocks[indexOfCurrentBlock]->relayed_by);
				fscanf(fp, "%s", buffer);
				fscanf(fp, "%s", blocks[indexOfCurrentBlock]->prev_block);
				fscanf(fp, "%s", buffer);
				indexOfCurrentBlock++;
			}
			fclose(fp);
		}
	}
	return blocks;
}

void printOneBlock(Block *block)
{
	printf("hash: %s\n", block->hash);
	printf("height: %s\n", block->height);
	printf("total: %s\n", block->total);
	printf("time: %s\n", block->time);
	printf("received_time: %s\n", block->received_time);
	printf("relayed_by: %s\n", block->relayed_by);
	printf("prev_block: %s\n", block->prev_block);
}

void freeBlocks(Block** blocks, int numberOfBlocks)
{
	for (int i = 0; i < numberOfBlocks; i++)
	{
		free(blocks[i]);
	}
	free(blocks);
}
