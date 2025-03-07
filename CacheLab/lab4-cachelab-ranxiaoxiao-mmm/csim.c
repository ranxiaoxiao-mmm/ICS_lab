#include "cachelab.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csim.h"
#include <getopt.h>
#include <limits.h>
#include <math.h>

void usage()
{
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file> -q <policy>\n");
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("  -q <policy>  Replacement policy (LRU or 2Q)\n");
    printf("\n");
    printf("Examples:\n");
    printf("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace -q LRU\n");
    printf("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace -q 2Q\n");
    exit(1);
}

// parse command line and get the parameters
void parseline(int argc, char **argv)
{
    int opt;
    int num = 0;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:q:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            usage();
            break;
        case 'v':
            verbose = 1;
            break;
        case 's':
            num = atoi(optarg);
            if (num == 0 && optarg[0] != '0')
            {
                printf("./csim: Missing required command line argument\n");
                usage();
            }
            numSet = num;
            break;
        case 'E':
            num = atoi(optarg);
            if (num == 0 && optarg[0] != '0')
            {
                printf("./csim: Missing required command line argument\n");
                usage();
            }
            associativity = num;
            break;
        case 'b':
            num = atoi(optarg);
            if (num == 0 && optarg[0] != '0')
            {
                printf("./csim: Missing required command line argument\n");
                usage();
            }
            blockSize = num;
            break;
        case 't':
            strcpy(filePath, optarg);
            break;
        case 'q':
            if (strcmp(optarg, "LRU") == 0 || strcmp(optarg, "2Q") == 0)
            {
                if (strcmp(optarg, "LRU") == 0)
                    policy = 0;
                else
                    policy = 1;
            }
            else
            {
                fprintf(stderr, "Invalid replacement policy: %s\n", optarg);
                exit(1);
            }
            break;
        case ':':
            printf("./csim: Missing required command line argument\n");
            usage();
            break;
        case '?':
            usage();
            break;
        default:
            printf("getopt error");
            exit(1);
            break;
        }
    }
}

void create_cache(){
    cache = malloc(numSet * sizeof(line*));
    if(policy){
        A1_in = malloc(sizeof(Queue*) * numSet);
    }

    for(int i = 0;i < numSet;i++){
        cache[i] = malloc(associativity * sizeof(line));
        if(policy){
            A1_in[i] = create_queue();
        }
        for(int j = 0;j < associativity;j++){
            (cache[i][j]).valid = 0;
        } //初始化有效位为0

    }
}

void free_cache(){
    for(int i = 0;i < numSet;i++){
        free(cache[i]);
        if(policy){
            free(A1_in[i]);
        }
    }

    free(cache);
    if(policy){
        free(A1_in);
    }
}

int LRU(int set){
    int oldest = -1; //记录最大年龄
    int LRUline; //返回的LRU行

    for(int i = 0;i < associativity;i++){
        if((cache[set][i]).age > oldest){
            oldest = (cache[set][i]).age;
            LRUline = i;
        }
    }

    return LRUline;
}

void renewage(int set, int line){
    for(int i = 0;i < associativity; i++){
        if(i == line){
            (cache[set][i]).age = 0; //更新年龄
        }
        else{
            (cache[set][i]).age += 1; //年龄+1
        }
    }
}

void Simulate(){
    FILE *file = fopen(filePath,"r");

    unsigned long int set, tag; //记录目标set\tag
    bool b_hit, b_evic; //判断是否发生命中、替换
    int newline;

    char op; //记录操作
    unsigned long long addr; //记录地址
    int size; //记录操作大小

    while(fscanf(file, " %c %llx,%d", &op, &addr, &size) > 0){ //fscanf会返回读取的变量数
        b_hit = false;
        b_evic = false;
        newline = 0;

        if(op == 'I'){
            continue;
        }
        else if(verbose){
            printf("%c %llx,%d ", op, addr, size);
        }

        set = (addr / blockSize) % numSet; //计算目标set
        tag = addr / (numSet * blockSize); //计算目标tag

//判断是否命中缓存
        for(int i = 0;i < associativity;i++){
            if((cache[set][i]).valid == 1 && (cache[set][i]).tag == tag){
                b_hit = true;
                renewage(set,i); //更新年龄，便于LRU操作
                break;
            }
            else if((cache[set][i]).valid==0 && newline == 0){
                newline = i+1; //保证当i=0时，也可以通过newline直接判断是否有缓存空行
            }
        }

        if(!b_hit){
            if(policy == 0){
                if(newline){ //找到了空cacheline，直接存储
                    b_evic = false;
                    (cache[set][newline-1]).valid = 1;
                    (cache[set][newline-1]).tag = tag;
                    renewage(set,newline-1); //写入后还会再读取一次，肯定会hit，所以直接renewage
                }
                else{
                    b_evic = true;
                    newline = LRU(set); //进行LRU替换
                    (cache[set][newline]).valid = 1;
                    (cache[set][newline]).tag = tag;
                    renewage(set,newline); //同上
                }
            }
            else if(policy == 1){
                if(find_and_remove(A1_in[set],tag) == 1){ //A1_in中找到了tag
                    if(newline){ //找到了空cacheline，直接存储 --> Am未满
                        b_evic = false;
                        (cache[set][newline-1]).valid = 1;
                        (cache[set][newline-1]).tag = tag;
                        renewage(set,newline-1); //写入后还会再读取一次，肯定会hit，所以直接renewage
                   }
                    else{
                        b_evic = true;
                        newline = LRU(set); //进行LRU替换
                        (cache[set][newline]).valid = 1;
                        (cache[set][newline]).tag = tag;
                        renewage(set,newline); //同上
                    }
                }
                else{ //A1_in中未找到tag
                    if(A1_in[set]->size < associativity){
                        enqueue(A1_in[set],tag); //A1_in未满，直接加入
                    }
                    else if(A1_in[set]->size >= associativity){
                        dequeue(A1_in[set]); //A1_in满，先出队再入队
                        enqueue(A1_in[set],tag);
                    }
                }
            }
        }

//计算对应hit、miss、eviction的次数
        switch(op){
            case 'L':
                if(b_hit){ //命中
                    hit += 1;
                    if(verbose){
                        printf("hit\n");
                    }
                }
                else if(b_evic){//不命中且替换
                    miss += 1;
                    eviction += 1;
                    if(verbose){
                        printf("miss eviction\n");
                    }
                }
                else{//不命中直接更新，无替换
                    miss += 1;
                    if(verbose){
                        printf("miss\n");
                    }
                }
                break; 
            
            case 'S':
                if(b_hit){ //命中
                    hit += 1;
                    if(verbose){
                        printf("hit\n");
                    }
                }
                else if(b_evic){//不命中且替换
                    miss += 1;
                    eviction += 1;
                    if(verbose){
                        printf("miss eviction\n");
                    }
                }
                else{//不命中直接更新，无替换
                    miss += 1;
                    if(verbose){
                        printf("miss\n");
                    }
                }
                break; 
            
            case 'M':
                if(b_hit){ //命中，读一次中写一次中
                    hit += 2;
                    if(verbose){
                        printf("hit hit\n");
                    }
                }
                else if(b_evic){//不命中且替换
                    miss += 1;
                    eviction += 1;
                    hit += 1;
                    if(verbose){
                        printf("miss eviction hit\n");
                    }
                }
                else{//不命中直接更新，无替换
                    miss += 1;
                    hit += 1;
                    if(verbose){
                        printf("miss hit\n");
                    }
                }
                break; 
            
        }

    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    parseline(argc, argv);
    create_cache();
    Simulate();
    free_cache();
    printSummary(hit, miss, eviction);
    return 0;
}