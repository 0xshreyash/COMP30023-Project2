#include "input_handler.h"

#include <errno.h>
#include <inttypes.h>
#include <pthread.h>

#include <sys/types.h> 
#include <sys/socket.h>

#include <netinet/in.h>

#include "server.h"
#include "work_handler.h"

#define LONGEST_SEQUENCE 64
#define DIFFICULTY_LEN 8
#define SEED_LEN 64
#define NONCE_LEN 16

void input_handler(char* buffer, int sd) {
    
    if(strncmp(buffer, PING, 4) == 0) {
        fprintf(stdout, "PING received");
        my_send(PONG, sd);
    }
    else if(strncmp(buffer, PONG, 4) == 0) {
        reply_to_pong(sd); 
    }
    else if(strncmp(buffer, ERRO, 4) == 0) {
        reply_to_erro(sd); 
    }
    else if(strncmp(buffer, OKAY, 4) == 0) {
        reply_to_okay(sd); 
    }
    else if(strncmp(buffer, SOLN, 4) == 0) {
        reply_to_soln(buffer, sd); 
    }
    else if(strncmp(buffer, WORK, 4) == 0) {
        reply_to_work(buffer, sd); 
    }
    else if(strncmp(buffer, ABRT, 4) == 0) {
        client_abort(sd); 
    }
    else {
        reply_to_gibberish(sd); 
    }
}

void reply_to_pong(int sd) {
    // Log here
    fprintf(stdout, "PONG received");
    char *suffix = "PONG message reserved for the server only";
    char *error_message = form_error(suffix);
    my_send(error_message, sd); 
}

void reply_to_soln(char* buffer, int sd) {
    
    SOLN_ARGS args;
    char *check = malloc(sizeof(char) * (LONGEST_SEQUENCE + 1));

    // Get rid of the word SOLN
    strtok(buffer, " ");
    strcpy(check, strtok(NULL, " "));
    if(strlen(check) != DIFFICULTY_LEN) {
        fprintf(stdout, "Client WORK message invalid");
    }
}

void reply_to_erro(int sd) {
    char *suffix = "ERRO messages can only be sent by the server";
    char *error_message = form_error(suffix); 
    my_send(error_message, sd); 
}

void reply_to_work(char* buffer, int sd) {
    my_send("Nothing here yet", sd); 
}

void client_abort(int sd) {

}

void reply_to_okay(int sd) {
    char *suffix = "ERRO messages can only be sent by the server";
    char *error_message = form_error(suffix); 
    my_send(error_message, sd); 
}

void reply_to_gibberish(int sd) {
    char *suffix = "Sent message not part of the protocol";
    char *error_message = form_error(suffix); 
    my_send(error_message, sd); 
}

char *form_error(char *suffix) {
    // + 1 for space
    char *error = malloc(sizeof(char) * (HEADER_LENGTH + strlen(suffix) + 1));
    memset(error, 0, HEADER_LENGTH + strlen(suffix + 1)); 
    strcpy(error, ERRO); 
    strcat(error, suffix);
    strcat(error, CRLF); 
    error[strlen(error)] = '\0'; 
    return error;
}

void my_send(char message[MAX_MESSAGE_LEN], int sd) {
    // Protocol messages sent need to be formatted according to SSTP.
    char protocol_message[MAX_MESSAGE_LEN + HEADER_LENGTH + 1];
    memset(protocol_message, 0, MAX_MESSAGE_LEN + HEADER_LENGTH + 1);
    strcat(protocol_message, (char*)message);
    strcat(protocol_message, "\r\n");
    int n = send(sd, (BYTE *)protocol_message, strlen(protocol_message), 0); 
    if (n !=  strlen(protocol_message)) {
		perror("ERROR while writing to socket");
		//exit(EXIT_FAILURE);
	}
    else {
        // Log here.
    }
    return;
}

