/* 
 * Module for creating and manipulating queues of arbitrary data types 
 * created for COMP20007 Design of Algorithms 2017
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au> and modified by 
 * Shreyash Patodia <spatodia@student.unimelb.edu.au> to allow for 
 * arbitraty data types and also to have certain function required for
 * COMP30023, Project-1. 
 */

#include <stdlib.h>
#include <assert.h>
#include "queue.h"

/*********************** Structure Definitions **************************/

// a Queue is just a wrapper for a list of its items
// we will use the back of the list as the entry point, and the front as the 
// exit point (to take advantage of O(1) insert and remove operations)
struct queue {
	List *items;
};


/*********************** Function Definitions ****************************/


/*********************   Shreyash's Functions ****************************/

/*
 * Gets the next node in the queue 
 */
Node *queue_get_next(Node *node) {
	return get_next(node);
}

/*
 * Get the data from a node in the queue
 */
void *queue_get_data(Node *node) {
	return get_data(node);
}

/* 
 * Gets the head of the queue.
 */
Node *queue_get_head(Queue *queue) {
	return get_head(queue->items);
} 

/*
 * Calls the appropriate list function to remove a process
 * from anywhere in the queue (list);
 */
void *queue_remove_from_middle(Queue *queue, Node *node) {
	return remove_from_middle(queue->items, node);
}

/**********************  Matt's Functions ********************************/

// create a new queue and return its pointer
Queue *new_queue() {
	Queue *queue = malloc(sizeof *queue);
	assert(queue);

	queue->items = new_list();
	
	return queue;
}

// destroy a queue and its associated memory
void free_queue(Queue *queue) {
	assert(queue != NULL);
	// free the list of items, and the queue itself
	free_list(queue->items);
	free(queue);
}

// insert a new item at the back of a queue. O(1).
void queue_enqueue(Queue *queue, void *data) {
	
	assert(queue != NULL);
	// use the back of the list as the entry point
	list_add_end(queue->items, data);
}

// remove and return the item at the front of a queue. O(1).
// error if the queue is empty (so first ensure queue_size() > 0)
void *queue_dequeue(Queue *queue) {
	assert(queue != NULL);
	assert(queue_size(queue) > 0);

	// use the front of the list as the exit point
	return list_remove_start(queue->items);
}

// return the number of items currently in a queue
int queue_size(Queue *queue) {
	assert(queue != NULL);
	// delegate straight to list size function
	return list_size(queue->items);
}

/*void queue_remove(Queue *queue, void *data) {
	list_remove(queue->items, data);
	
}*/

/**************************************************************************/



