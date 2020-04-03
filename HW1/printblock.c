#include"Utilities.h"

void printBlockByValue(Block** blocks, int numberOfBlocks,char* field, char* value)
{
	int i;
	if (strstr(field, "hash") != NULL)
	{
		for (i = 0; i < numberOfBlocks; i++)
		{
			if (strcmp(blocks[i]->hash, value) == 0)
			{
				printOneBlock(blocks[i]);
				break;
			}
		}
		if (i == numberOfBlocks)
		{
			printf("There are no blocks with hash value %s\n", value);
		}
	}
	else if (strstr(field, "height") != NULL)
	{
		for (i = 0; i < numberOfBlocks; i++)
		{
			if (strcmp(blocks[i]->height, value) == 0)
			{
				printOneBlock(blocks[i]);
				break;
			}
		}
		if (i == numberOfBlocks)
		{
			printf("There are no blocks with height value %s\n", value);
		}
	}
	else
	{
		printf("You cant serach for %s filed only (hash) or (height)\n", field);
	}
}


int main(int argc, char** argv)
{
	int numberOfBlocks = getHowManyBlocksInTheFile();
	Block** blocks = loadBlocksFromFile(numberOfBlocks);
	printBlockByValue(blocks, numberOfBlocks, argv[1], argv[2]);
	freeBlocks(blocks, numberOfBlocks);
	return 0;
}
