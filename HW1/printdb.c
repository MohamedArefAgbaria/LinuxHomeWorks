#include"Utilities.h"

void printBlocks(Block** blocks, int numberOfBlocks)
{
	for (int i = 0; i < numberOfBlocks; i++)
	{
		printOneBlock(blocks[i]);
		if (i != numberOfBlocks - 1)
		{
			printf("                             |\n");
			printf("                             |\n");
			printf("                             |\n");
			printf("                             V\n");
		}
	}
}

int main()
{
	int numberOfBlocks = getHowManyBlocksInTheFile();
	Block** blocks = loadBlocksFromFile(numberOfBlocks);
	printBlocks(blocks, numberOfBlocks);
	freeBlocks(blocks, numberOfBlocks);
	return 0;
}
