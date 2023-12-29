
#ifndef _SORT_LIST_H_
#define _SORT_LIST_H_
/*
 * add element with value data to the sorted linked list
 */
void sort_list_insert(sl_handle*, int);

/*
 * search for the element with value data and
 * remove from the sorted linked list
 */
void sort_list_remove(sl_handle*, int);

/*
 * search an element for the data in the sorted linked list
 * and return its index if found
 */
sl_node* sort_list_search(sl_handle*, int);

/*
 * traverse all items of the sorted list and display the elements
 */
void sort_list_display(sl_handle*);


sl_handle* sort_list_init();

void sort_list_cleanup(sl_handle* );
#endif /*_SORT_LIST_*/

