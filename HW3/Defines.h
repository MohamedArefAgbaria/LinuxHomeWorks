
#ifndef __DEFINES_H
#define __DEFINES_H
#include <mqueue.h>
#include <unistd.h>
#define BLOCKDIFFICULTY 16
#define MAXAMOUNTMINERS 20
#define NUMBEROFBLOCKS 200
#define MINER_MQ_NAME "/miner_mq"
#define SERVER_MQ_NAME "/server_mq"
#define MQ_MAX_MSG_SIZE sizeof(BLOCK_T)
#define MQ_MAX_SIZE 10
#endif