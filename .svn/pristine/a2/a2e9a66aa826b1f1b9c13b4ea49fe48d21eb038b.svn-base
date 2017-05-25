#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "sha256.h"
#include "server.h"

#define HEADER_LENGTH 4

void input_handler(char* buffer, int sd);

void reply_to_ping(int sd);

void reply_to_pong(int sd);

void reply_to_soln(char* buffer, int sd);

void reply_to_erro(int sd);

void reply_to_work(char* buffer, int sd);

void client_abort(int sd); 

void reply_to_okay(int sd);

void reply_to_gibberish(int sd);

char *form_error(char *suffix);

void my_send(char message[MAX_MESSAGE_LEN + HEADER_LENGTH + 2], int sd); 

#endif