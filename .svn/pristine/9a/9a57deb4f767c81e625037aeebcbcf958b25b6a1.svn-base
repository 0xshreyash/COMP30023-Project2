#include "server.h"

#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  
#include <stdbool.h>
#include <signal.h>

#include "input_handler.h"

#define TRUE   1 
#define FALSE  0

/**
 * The code here is very similar to the code explained in the following
 * resources: 
 * http://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
 * http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#select
 *
 * The code has been appropriated to fit into the assignment spec
 */
int main(int argc, char *argv[]) {
    signal(SIGPIPE, SIG_IGN);
    if(argc < 2) {
        fprintf(stderr, "Please provide a port");
        exit(EXIT_SUCCESS);
    }
    int opt = TRUE; 
    int master_socket, new_socket, port_no;
    int no_client; 
    int max_sd, activity, sd, len;
    char *temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    struct sockaddr_in myaddr;
    Client clients[MAX_CLIENTS]; 
   
    fd_set readfds;

    memset(temp, 0, BUFFER_SIZE + 1);

    for(int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].socket = 0;
        clients[i].buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); 
        memset(clients[i].buffer, 0, BUFFER_SIZE + 1);
    }

    if((master_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error opening socket. Please try again.");
        exit(EXIT_FAILURE);
    }

    /*
    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
       sizeof(opt)) < 0 )  {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    } 
    */

    memset(&myaddr, 0, sizeof(myaddr));
    port_no = atoi(argv[1]);
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port_no);
	myaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(master_socket, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {  
        perror("Binding failed. Please try again.");  
        exit(EXIT_FAILURE);
    }

    if (listen(master_socket, MAX_CLIENTS) < 0) {  
        perror("Something went wrong when listening to the clients");  
        exit(EXIT_FAILURE);  
    }

    while(TRUE) {
        //fprintf(stdout, "Fine here"); 
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds); 
        max_sd = master_socket;
        for(int i = 0; i < MAX_CLIENTS; i++) {
            sd = clients[i].socket;
             //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
            //Highest file descriptor number needed for select. 
            if(sd > max_sd)  
                max_sd = sd;
        }
        // Wait for activity in one of the sockets, no write or except
        // sockets. No timeout either, can timeout if needed.
        activity = select(max_sd + 1 , &readfds , NULL , NULL , NULL);
        if ((activity < 0) && (errno!=EINTR)) {  
            fprintf(stdout, "Select error");  
        }  
        //If something happened on the master socket, 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds)) {  
            int socket_length = sizeof(myaddr); 
            if ((new_socket = accept(master_socket, 
            (struct sockaddr *)&myaddr, (socklen_t*)&socket_length))<0) {  
                perror("Accept Error");
            }
            
            //add new socket to array of sockets 
            for (int i = 0; i < MAX_CLIENTS; i++) {  
                //if position is empty 
                if(clients[i].socket == 0) {  
                    clients[i].socket = new_socket;  
                    //fprintf(stderr, "Adding to list of sockets as %d\n" , i);  
                    break;  
                }  
            }  
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {  
            sd = clients[i].socket;  
            
            if (FD_ISSET(sd , &readfds)) {
                if ((len = read(sd, temp, BUFFER_SIZE)) == 0) {
                    close(sd);
                    clients[i].socket = 0;
                    memset(clients[i].buffer, 0, BUFFER_SIZE + 1); 
                }
                // Max message len has been reached, ask client to dial it down
                // a bit. 
                if(len + strlen(clients[i].buffer) > BUFFER_SIZE) {
                    char *too_long_error = form_error("The message is too long");
                    my_send(too_long_error, sd); 
                    continue;
                    // NEED TO CHANGE THIS. 
                    // exit(EXIT_FAILURE); 
                }
                else {
                    strcat(clients[i].buffer, temp); 
                    memset(temp, 0, BUFFER_SIZE + 1); 
                }
                // Optimise me in case of timeouts. 
                int j = 0;
                while(clients[i].buffer[j] != '\0') {
                    char *rest_message = malloc(sizeof(char) * (BUFFER_SIZE + 1));
                    char *first_message = malloc(sizeof(char) * (BUFFER_SIZE + 1)); 
                    memset(rest_message, 0, BUFFER_SIZE + 1); 
                    if(j != BUFFER_SIZE - 1 && clients[i].buffer[j] == '\r' && 
                    clients[i].buffer[j + 1] == '\n') {
                        if(strcmp(clients[i].buffer, "PING\r\n") != 0 && strcmp(clients[i].buffer, "PONG\r\n") != 0) {
                            fprintf(stdout, "Buffer inside check is : %s\n", clients[i].buffer);
                        }
                        fflush(stdout); 
                        strncpy(first_message, clients[i].buffer, j);
                        first_message[j] = '\0';
                        strcpy(rest_message, clients[i].buffer + j + 2);
                        // fprintf(stdout, "Message is: %s\n", first_message);
                        input_handler(first_message, sd);
                        clients[i].buffer[0] = '\0'; 
                        strcpy(clients[i].buffer, rest_message); 
                        clients[i].buffer[strlen(clients[i].buffer)] = '\0';
                        free(rest_message);
                        free(first_message);
                        if(strcmp(clients[i].buffer, "PING\r\n") != 0 && strcmp(clients[i].buffer, "PONG\r\n") != 0
                        && strcmp(clients[i].buffer, "") != 0) {
                            fprintf(stdout, "Buffer towards end is : %s\n", clients[i].buffer);
                        }
                        j = 0;
                    }
                    else {
                        j++;
                    }
                }
            }  
        }    
    }
    close(master_socket);
    return EXIT_SUCCESS;
}

