/* 
 * Module for creating and manipulating doubly-linked lists of integers
 *
 * created for COMP20007 Design of Algorithms 2017 
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au> and used by Shreyash
 * Patodia, <spatodia@student.unimelb.edu.au> Student ID: 767337, 
 * login: 767336 for COMP30023, Assignemnt - 1. 
 */
#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

/**************** Typedef structs *******************************/

typedef struct list List;
typedef struct node Node;


/************* Shreyash's function declarations ****************/

/*
 * Finds the next node to the previous node
 *
 * params -
 * node the node who's next node is to be found
 *
 * return -
 * the next node to the node passed as parameter, may be null. 
 */
Node *get_next(Node *node);

/*
 * Gets the data from a given node.
 *
 * params - 
 * node - the node to get the data of.
 * 
 * return -
 * the data in the node as a void * type. 
 */
void *get_data(Node *node);

/*
 * Returns the head of the list as a node. 
 *
 * params -
 * list the list who's head is to be returned
 * 
 * return -
 * the head of the list
 */
Node *get_head(List *list);

/*
 * Removes a Node from the list, irrespective of the
 * position of the node and returns the data stored
 * in it.
 *
 * params -
 * list the list to remove the node from
 * node the node to remove. 
 * 
 * return -
 * the data in the node just removed.
 */
void *remove_from_middle(List *list, Node *node);

/*********** Matt's function declarations ********************/

// create a new list and return its pointer
List *new_list();

// destroy a list and free its memory
void free_list(List *list);

// add an element to the front of a list
// this operation is O(1)
void list_add_start(List *list, void *data);

// add an element to the back of a list
// this operation is O(1)
void list_add_end(List *list, void *data);

// remove and return the front data element from a list
// this operation is O(1)
// error if the list is empty (so first ensure list_size() > 0)
void *list_remove_start(List *list);

// remove and return the final data element in a list
// this operation is O(n), where n is the number of elements in the list
// error if the list is empty (so first ensure list_size() > 0)
void *list_remove_end(List *list);

// return the number of elements contained in a list
int list_size(List *list);

// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list);

/********************************************************************/
#endif