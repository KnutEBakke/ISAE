/**
 * @file binary-heap.h
 *
 * @brief Simple definition of a binary heap containing `event` values
 *
 * @author Knut Bakke
 *
 * This is a simple definition of a binary heap containing `event`
 * values implemented using a binary tree. Warning: the cells
 * pointers should not be shared as deallocation of a BST
 * deallocates the memory space reserved for the cells!
 *
 * Inserting a value and extracting the minimum value are guaranteed
 * to have a worst-case complexity in $O(\log n)$ where $n$ is the
 * size of the heap.
 *
 * The API of the binary heap is defined as follows:
 *
 * - a function to create an empty heap
 * - a function to check if the heap is empty
 * - a function to insert a new value in the heap
 * - a function to get the minimum value in the heap
 * - a function to print the binary heap
 * - a function to deallocate the binary heap
 */

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "event.h"

/**
 * @brief An alias to the structure representing the nodes of the
 *        binary heap.
 */
typedef struct heap_event_node heap_event_node;

/**
 * @brief The structure representing the nodes of the binary heap.
 */
struct heap_event_node {
    /** The value in the node */
    event*            p_event;
    /** A pointer to the left child node */
    heap_event_node *left;
    /** A pointer to the right child node */
    heap_event_node *right;
    /** A pointer to the father node */
    heap_event_node *father;
};

/**
 * @brief An alias to the structure representing a binary heap.
 */
typedef struct heap_event heap_event;

/**
 * @brief The structure representing the binary heap.
 */
struct heap_event {
    /** The root of the binary heap. May be `NULL` */
    heap_event_node *root;
    /** The size of the binary heap */
    int            size;
};

/**
 * @brief Create a nil binary heap.
 *
 * @return a new empty binary heap
 */
heap_event nil_heap(void);

/**
 * @brief Create a nil heap node.
 *
 * @return a pointer to a new empty heap node.
 */

heap_event_node* nil_node(void);

/**
 * @brief Is the binary heap empty?
 *
 * @param p_heap a pointer to the heap you want to
 *               check the emptiness
 *
 * @return `true` is `p_heap` is empty, `false` else
 *
 * @pre `p_heap` is not `NULL`
 */
bool is_empty(heap_event *p_heap);

/**
 * @brief Is the binary heap not empty?
 *
 * @param p_heap a pointer to the heap you want to
 *               check the emptiness
 *
 * @return `false` is `p_heap` is empty, `true` else
 *
 * @pre `p_heap` is not `NULL`
 */
bool is_not_empty(heap_event *p_heap);


/**
 * @brief Insert a new value in the binary heap. The
 *        worst-case execution time of this function
 *        is guaranteed to be in \f$\log n\f$ where
 *        \f$n\f$ is the size of the binary heap.
 *
 * @param p_heap a pointer to the heap in which the event is
 *               to be inserted
 * @param p_e  a pointer to the event to be inserted
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, `p_heap` will point to a binary heap
 *       in which the event `e` has been inserted according
 *       to the algorithm presented in the lab session.
 */
void insert(heap_event *p_heap, event* p_e);

/**
 * @brief Extract the minimum node in the binary heap. The
 *        worst-case execution time of this function
 *        is guaranteed to be in \f$\log n\f$ where \f$n\f$ is
 *        the size of the binary heap.
 *
 * @param p_heap a pointer to the heap from which the node is
 *               to be extracted
 *
 * @return the minimum node in the binary heap
 *
 * @pre `p_heap` is not `NULL` and the binary heap is not empty
 */
heap_event_node* extract_min(heap_event *p_heap);

/**
 * @brief Prints the binary heap.
 *
 * @param p_heap a pointer to the binary heap to be printed
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, the binary heap is printed.
 */
void print_heap(heap_event *p_heap);

/**
 * @brief Deallocate the binary heap.
 *
 * @param p_heap  a pointer to the binary heap to be deallocated
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, all memory regions used for the nodes
 *       are deallocated.
 */
void deallocate_heap(heap_event *p_heap);

/**
 * @brief Find the father node.
 * 
 * @param p_heap a pointer to the binary heap where you find the father.
 * 
 * @param n an int representing the position of the fathers child.
 * 
 * @pre 'p_heap' is not 'NULL'
 * 
 * @pre 'n' is a positiv integer.
 * 
 */
heap_event_node* go_to_father_node(heap_event*, int n);

#endif
