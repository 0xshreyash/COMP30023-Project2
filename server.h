#ifndef SERVER_H
#define SERVER_H

/* Stand-alone messages */ 
#define PING "PING\r\n"
#define PONG "PONG\r\n"
#define OKAY "OKAY\r\n"
#define ABRT "ABRT\r\n"

/* Messages that have some suffix */
#define ERRO "ERRO"
#define SOLN "SOLN"
#define WORK "WORK"

#define MAX_CLIENTS 100
#define MAX_PENDING_JOBS 10



#include "uint256.h"
#include "sha256.h"

#endif