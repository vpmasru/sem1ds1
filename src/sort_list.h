
#ifndef _SORT_LIST_H_
#define _SORT_LIST_H_
/*
 * add element with value data to the sorted linked list
 */
void sort_list_insert(int data);

/*
 * search for the element with value data and
 * remove from the sorted linked list
 */
void sort_list_remove(int data);

/*
 * search an element for the data in the sorted linked list
 * and return its index if found
 */
int sort_list_search(int data);

/*
 * traverse all items of the sorted list and display the elements
 */
void sort_list_display(void);

/*
 * fetch the sorted list entry stored at index 
 */
int 
sort_list_get_item_by_index(int index, int *record);

#endif /*_SORT_LIST_*/

