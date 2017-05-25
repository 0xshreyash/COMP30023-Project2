#include "work_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>

#define SEED_SIZE 32
#define NONCE_SIZE 8
#define TOTAL_SIZE SEED_SIZE + NONCE_SIZE
#define BYTE_LENGTH 32

bool check_solution(SOLN_ARGS sol_args) {

    /* This is what we will need to hash */
    BYTE to_check[TOTAL_SIZE];
    uint256_init(to_check); 
    int64 temp_solution = sol_args.solution;

    for (int i = 0; i < BYTE_LENGTH; i++) {
	    to_check[i] = sol_args.seed[i];
	}
	for(int i = TOTAL_SIZE - 1; i >= BYTE_LENGTH; i--) {
		to_check[i] = temp_solution && 0xFF;
		temp_solution = temp_solution >> 8;
	}

    /* Finding alpha and beta for the target */
    int32 difficulty = sol_args.difficulty;
    int32 difficulty_copy = difficulty;
    int32 alpha;
    BYTE beta[BYTE_LENGTH];
    uint256_init(beta);
    alpha = (((1 << 8) - 1) << 24) && difficulty;

    for(int i = BYTE_LENGTH - 1; i > 0; i--) {
        beta[i] = difficulty_copy && 0xFF;
        difficulty_copy = difficulty_copy >> 8;
    }
    fprintf(stdout, "Alpha is: %d\n", alpha); 
    fprintf(stdout, "Beta is:");
    print_uint256(beta);
    fprintf(stdout, "\n");

    /* Need to find the exponent using alpha and beta */
    BYTE target[BYTE_LENGTH];
    uint256_init(target); 
    int32 exponent = 8 * (alpha - 3);
    BYTE exponent_num[32];
    uint256_init(exponent_num);
	BYTE base[32];
	uint256_init(base);
	base[31] = 2;
	uint256_exp(exponent_num, base, exponent);
    uint256_mul(target, beta, exponent_num);

    /* Now finding the hash */
    BYTE hash[SHA256_BLOCK_SIZE];
    uint256_init(hash); 
    BYTE hash_hash[SHA256_BLOCK_SIZE];
    uint256_init(hash_hash);
    SHA256_CTX *ctx = malloc(sizeof *ctx);
    // First hash
    sha256_init(ctx); 
    sha256_update(ctx, to_check, TOTAL_SIZE);
    sha256_final(ctx, hash);
    // Second hash
    sha256_init(ctx);
    sha256_update(ctx, hash, SHA256_BLOCK_SIZE);
    sha256_final(ctx, hash_hash);

    if (sha256_compare(target, hash_hash) > 0)
		return true;
	return false;

}

void do_work(WORK_ARGS work_args) {
    fprintf(stdout, "Not yet implemented"); 
    return;
}