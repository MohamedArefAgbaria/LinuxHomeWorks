#ifndef __BLOCK_H
#define __BLOCK_H
typedef struct block 
{
	char hash[1024];
	char height[1024];
	char total[1024];
	char time[1024];
	char received_time[1024];
	char relayed_by[1024];
	char prev_block[1024];
}Block;
#endif 
