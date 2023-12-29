#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "sort_list.h"


/* sorting logic using linear search */

/*
 * sorted linked list init.
 */
sl_handle* sort_list_init()
{
    return (sl_list_init(1));
}


/*
 * add element with value data to the sorted linked list
 * element < front add at front.
 * element > rear add at rear.
 * element > front < rear , identify postion and insert. avoid duplicate.
 */
void sort_list_insert(sl_handle *handle, int data)
{
    int rc;

    if ((sl_list_empty(handle)) || 
                     ((handle->front) && (data < handle->front->key))) {
       rc =  sl_list_push(handle, data, INSERT_FRONT);
       if (rc == LIST_ERROR) {
           printf("Failed to insert Node: %s:%d\n",__FUNCTION__, __LINE__);
           return;
       }
    }
    else if ((handle->rear) && (data > handle->rear->key)) {
       rc =  sl_list_push(handle, data, INSERT_REAR);
       if (rc == LIST_ERROR) {
           printf("Failed to insert Node: %s:%d\n",__FUNCTION__, __LINE__);
          return;
       }
    }
    else {
        sl_node *temp = handle->front;
        while (temp != NULL) {
            if ((temp->next) && (temp->key < data)
                        && (temp->next->key > data)) {
                break;
            }
            temp = temp->next;
        }
        if (temp) {
            handle->pos = temp;
            rc = sl_list_push(handle, data, INSERT_NEXT);
            if (rc == LIST_ERROR) {
               printf("Failed to insert Node: %s:%d\n",__FUNCTION__, __LINE__);
               return;
            }
        }
    }
    return;
}

/*
 * search for the element with value data and
 * remove from the sorted linked list
 */
void sort_list_remove(sl_handle *handle, int data)
{
    sl_node* temp = NULL;
    sl_node* pos = sort_list_search(handle, data);
    if (pos) {
        if (pos == handle->front) {
            sl_list_pop(handle, REMOVE_FRONT);
        } 
        else {
            /* traverse the list to remove an element */
            sl_node *temp = handle->front;
            while (temp) {
                if (temp->next == pos) break;
                temp = temp->next;
            }
            handle->pos = temp;
            sl_list_pop(handle,REMOVE_NEXT);
        }
    }

}

/*
 * search an element for the data in the sorted linked list
 */
sl_node* sort_list_search(sl_handle* handle, int data)
{
    if (handle->front->key == data) {
        return (handle->front);
    }
    else if (handle->rear->key == data) {
        return (handle->rear);
    }
    else {
        sl_node *pos = handle->front;
        while (pos != NULL) {
            if (pos->key == data) {
                return (pos);
            }
            pos = pos->next;
        }
    }
    return NULL;
}

/*
 * traverse all items of the sorted list and display the elements
 */
void sort_list_display(sl_handle *handle)
{
    int i = 1;
    sl_node *temp = handle->front;
    printf ("Sorted List start:\n");
    while (temp != NULL) {
        printf ("Element:%d, Key:%d\n",i++,temp->key);
        temp = temp->next;
    }
    printf ("Sorted List End:\n");
}

void sort_list_cleanup(sl_handle *handle) 
{
    sl_list_cleanup(handle);
}
#define TEST 0
#if TEST
int main()
{

sl_handle* handle = sort_list_init(1);
/* test empty */
sort_list_insert(handle, 10);
/* insert before head */
sort_list_insert(handle, 5);
/* insert at end */
sort_list_insert(handle, 29);
/* insert in mid */
sort_list_insert(handle, 15);
sort_list_insert(handle, 9);
sort_list_insert(handle, 21);
sort_list_insert(handle, 23);

sort_list_display(handle);
/* remove unknown */
sort_list_remove(handle,100);

sort_list_insert(handle, 7);
sort_list_insert(handle, 13);
/* insert in mid */
sort_list_display(handle);
/* remove from middle*/
sort_list_remove(handle, 15);
sort_list_remove(handle, 9);
sort_list_remove(handle, 10);

sort_list_display(handle);
/* remove already deleted */
sort_list_remove(handle, 10);
sort_list_remove(handle, 9);
sort_list_remove(handle, 15);


sort_list_display(handle);


}
#endif
