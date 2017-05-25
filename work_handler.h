#ifndef WORK_HANDLER_H 

#define WORK_HANDLER_H

#include <stdbool.h>

#include "uint256.h"
#include "sha256.h"
#include "server.h"

typedef uint32_t int32;
typedef uint64_t int64;

#define SEED_SIZE 32
#define NONCE_SIZE 8
#define TOTAL_SIZE SEED_SIZE + NONCE_SIZE
#define BYTE_LENGTH 32

typedef struct solution_arguments
{
    int32 difficulty;
    int64 nonce;
    BYTE seed[32];
} SOLN_ARGS;

typedef struct work
{
    Client client;
    int worker_count;
    int32 target;
    int64 nonce;
    BYTE x[BYTE_LENGTH + NONCE_SIZE];
} Work;

typedef struct helper_args {
    int64 start;
    int64 end;
    BYTE target[BYTE_LENGTH];
    BYTE x[BYTE_LENGTH + NONCE_SIZE];
} Helper; 

bool check_solution(SOLN_ARGS sol_args);

void do_work(Helper args);

#endif