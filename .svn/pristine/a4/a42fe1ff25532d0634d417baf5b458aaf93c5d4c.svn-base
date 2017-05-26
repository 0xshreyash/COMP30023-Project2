 # Created by Shreyash Patodia, 
 # login - spatodia, Student ID - 767336.
 # for COMP30023, Assignment-1.
 # 
 # Makefile that compiles the project.

CC     = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -O3

SRC =		server.c input_handler.c work_handler.c sha256.c list.c queue.c
OBJ =		server.o input_handler.o work_handler.o sha256.o list.o queue.o
EXE = 		server

# Creating the execuatable
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) -lm -lpthread

# Dependencies for each file
server.o:	  	 	server.h uint256.h sha256.h queue.h

sha256.o:	  	 	sha256.h

work_handler.o:		work_handler.h uint256.h sha256.h queue.h
input_handler.o: 	input_handler.h work_handler.h server.h sha256.h queue.h
queue.o: queue.h list.h
list.o: list.h

clean:
	rm -f $(OBJ)

clobber: clean
	rm $(EXE)

scp:
	scp *.c *.h Makefile digitalis:COMP30023-project
