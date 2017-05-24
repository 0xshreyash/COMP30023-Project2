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

#define BUFFER_SIZE 256
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

    if(argc < 2) {
        fprintf(stderr, "Please provide a port");
        exit(EXIT_SUCCESS);
    }
    int opt = TRUE; 
    int master_socket, new_socket_fd, port_no;
    int no_client; 
    int client_sockets[MAX_CLIENTS], max_sd, activity;
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    char *temp = malloc(sizeof(char) * BUFFER_SIZE);
    struct sockaddr_in myaddr;
   
    fd_set readfds;

    for(int i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }
    
    if((master_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error opening socket. Please try again.");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
       sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    } 

    memset(&myaddr, 0, sizeof(myaddr));
    port_no = atoi(argv[1]);
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port_no);
	myaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(master_socket, (struct sockaddr *)&myaddr, sizeof(myaddr))<0)  
    {  
        perror("Binding failed. Please try again.");  
        exit(EXIT_FAILURE);  
    }

    //try to specify maximum of 100 clients for the master socket 
    if (listen(master_socket, MAX_CLIENTS) < 0)  
    {  
        perror("Something went wrong when listening to the clients");  
        exit(EXIT_FAILURE);  
    }

    while(TRUE) {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds); 
        max_sd = master_socket;
        for(int i = 0; i < MAX_CLIENTS; i++) {
            
        }
    }

}

