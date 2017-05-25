/* 
 * Module for creating and manipulating queues of arbitrary data types 
 * created for COMP20007 Design of Algorithms 2017
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au> and modified by 
 * Shreyash Patodia <spatodia@student.unimelb.edu.au> to allow for 
 * arbitraty data types and also to have certain function required for
 * COMP30023, Project-1. 
 */

#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

/********************** Typedefing structures ***************************/

typedef struct queue Queue;

/*********************** Function Declarations ****************************/


/*********************   Shreyash's Functions ****************************/

/*
 * Gets the next node in the queue 
 */
Node *queue_get_next(Node *node);

/*
 * Get the data from a node in the queue
 */
void *queue_get_data(Node *node);

/* 
 * Gets the head of the queue.
 */
Node *queue_get_head(Queue *queue);

/*
 * Calls the appropriate list function to remove a process
 * from anywhere in the queue (list);
 */
void *queue_remove_from_middle(Queue *queue, Node *node);


/**********************  Matt's Functions ********************************/

// create a new queue and return its pointer
Queue *new_queue();

// destroy a queue and its associated memory
void free_queue(Queue *queue);

// insert a new item of data at the back of a queue. O(1).
void queue_enqueue(Queue *queue, void *data);

// remove and return the item of data at the front of a queue. O(1).
// error if the queue is empty (so first ensure queue_size() > 0
void *queue_dequeue(Queue *queue);

// return the number of items currently in a queue
int queue_size(Queue *queue);

// Removes items from the middle of the queue, useful for scheduling. 
//void queue_remove(Queue *queue, void *data);

Node *queue_get_next(Node *node);

void *queue_get_data(Node *node);

Node *queue_get_head(Queue *queue);

void *queue_remove_from_middle(Queue *queue, Node *node);

#endif
