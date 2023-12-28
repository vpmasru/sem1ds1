
#ifndef _LIST_H_
#define _LIST_H_


#define INSERT_FRONT 1
#define INSERT_REAR  2
#define REMOVE_FRONT 3
#define REMOVE_REAR  4

#define LIST_ERROR -1

typedef struct single_link_list {
    int key;
    struct single_link_list* next;
}sl_node;

/*
 * Initialize the list
 */
void sl_list_init();

/*
 * search the element with data value in the list and
 * return the index if found
 */
sl_node* sl_list_search(int);

/*
 * Insert the element with value data to the list
 */
int sl_list_push(int , char);

/*
 * remove the last element of the list
 */
void sl_list_pop(char);

/*
 * destroy the complete list
 */
void sl_list_cleanup(void);

void sl_list_display(void);

bool sl_list_empty(void);

int  sl_list_size(void);

#endif /*_LIST_H_*/
