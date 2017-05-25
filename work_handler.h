#ifndef WORK_HANDLER_H 

#define WORK_HANDLER_H

#include <stdbool.h>

#include "uint256.h"
#include "sha256.h"

typedef uint32_t int32;
typedef uint64_t int64;

typedef struct solution_arguments
{
    int32 difficulty;
    int64 nonce;
    BYTE seed[32];
} SOLN_ARGS;

typedef struct work_arguments
{
    int worker_count;
    int sockfd;
    int32 difficulty;
    int64 start;
    BYTE seed[32];
} WORK_ARGS;

bool check_solution(SOLN_ARGS sol_args);

void do_work(WORK_ARGS work_args);

#endif