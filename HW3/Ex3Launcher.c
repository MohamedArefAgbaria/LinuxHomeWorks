#include "lib.h"
#include "lib.c"
#include <mqueue.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int numOfMiners;
	sscanf(argv[1],"%d",&numOfMiners);
	char fullCommand[300] = "";
	char text1[10] = " & ";
	if (fork() == 0) //Server
	{
		system("./server.out");
		pause();
	}
	else
	{
	/* Create miners processes */
		sleep(1);
		for (int i = 1; i <= numOfMiners; i++)
		{
			char minerid[10];
			char command[30] = "./miner.out ";
			sprintf(minerid,"%d",i);
			strcat(command,minerid);
			if(i>1)
				strcat(fullCommand, text1);
			strcat(fullCommand, command);
		}
		system(fullCommand);
	}
	printf("all Done\n");
	return 0;
}

