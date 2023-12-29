
#ifndef _LIST_H_
#define _LIST_H_


#define INSERT_FRONT 1
#define INSERT_REAR  2
#define REMOVE_FRONT 3
#define REMOVE_REAR  4
#define INSERT_NEXT  5
#define REMOVE_NEXT  6
#define SEARCH_SUCCESS  7

#define LIST_ERROR -1

typedef struct single_link_list {
    int key;
    struct single_link_list* next;
}sl_node;

typedef struct list_handle {
    sl_node* front;
    sl_node* rear;
    sl_node *pos;
    int list_size;
}sl_handle;

/*
 * Initialize the list
 */
sl_handle* sl_list_init(char);

/*
 * search the element with data value in the list and
 * return the index if found
 */
sl_node* sl_list_search(sl_handle* ,int);

/*
 * Insert the element with value data to the list
 */
int sl_list_push(sl_handle*, int , char);

/*
 * remove the last element of the list
 */
void sl_list_pop(sl_handle* , char);

/*
 * destroy the complete list
 */
void sl_list_cleanup(sl_handle*);

void sl_list_display(sl_handle*);

bool sl_list_empty(sl_handle*);

int  sl_list_size(sl_handle*);

#endif /*_LIST_H_*/
