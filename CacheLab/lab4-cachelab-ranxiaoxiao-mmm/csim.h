#pragma once
#include <stddef.h>
#include "queue.h"

#define MININT -2147483648

// cache parameters
int numSet;
int associativity;
int blockSize;
char filePath[100];
int verbose = 0;
int policy;// 0 for LRU, 1 for 2Q

// final results
int hit = 0, miss = 0, eviction = 0;

// will be set in getopt() function
extern char *optarg;

typedef struct{
    int valid; //有效
    unsigned long int tag; //标记
    int age; //LRU判断是否最久未使用---计数器
} line;


line **cache; //cache存储数组
Queue **A1_in; //FIFO队列


// you can define functions here
void usage();
void parseline(int argc, char **argv);
void create_cache();
void free_cache();
void renewage(int set, int line);
int LRU(int set);
void Simulate();

