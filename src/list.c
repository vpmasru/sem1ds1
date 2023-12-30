#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

sl_handle sl_q_handle;
sl_handle sl_sort_handle;
/*
 * Initialize the list
 */
sl_handle* sl_list_init(char usecase)
{
    if (usecase == 0) {
        sl_handle* q_handle = &sl_q_handle;
        q_handle->front = NULL;
        q_handle->rear = NULL;
        q_handle->list_size = 0;
        return (q_handle);
    }
    else {
        sl_handle* s_handle = &sl_sort_handle;
        s_handle->front = NULL;
        s_handle->rear = NULL;
        s_handle->pos = NULL;
        s_handle->list_size = 0;
        return (s_handle);
    }
}

/*
 * search the element with data value in the list and
 * return node if found.
 */
sl_node* sl_list_search(sl_handle* handle, int key)
{
   sl_node* temp = handle->front;
    while (temp != NULL) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }
    return (NULL);  
}

/*
 * Insert the element with value data to the list
 */
int sl_list_push(sl_handle* handle, int key, char insert_from)
{
    sl_node* temp = NULL; 
    temp = malloc(sizeof(sl_node));
    if (temp == NULL) {
        /* Heap exhausted */
        printf("sl_list_push failed to alloc memory\n");
        return LIST_ERROR;
    }
    temp->key = key;
    temp->next = NULL;
    /* Incase list is empty make sure head=rear=first element */
    if (handle->list_size == 0) {
        handle->front = handle->rear = temp;
    }
    else {
        /* Add from rear */
        if ( insert_from == INSERT_REAR) {
            handle->rear->next = temp;
            handle->rear = temp;
        }
        else if (insert_from == INSERT_FRONT) {
            /* add from front */
            temp->next = handle->front;
            handle->front = temp;
        } 
        else {
            /* add in middle next to given position */
            if (handle->pos) {
                temp->next = handle->pos->next;
                handle->pos->next = temp;
                /* just to make sure we do not reuse this pointer */
                handle->pos = NULL;
            }
        }
    }
    handle->list_size++;
    return (0);
}


/*
 * remove the element with value data to the list
 */
void sl_list_pop(sl_handle* handle, char remove_from)
{
    if ((handle->front != NULL) && (remove_from == REMOVE_FRONT)) {
        sl_node* temp = handle->front;
        handle->front = handle->front->next;
        free(temp);
        handle->list_size--;
        if (handle->front == NULL) {
            handle->rear = NULL;
        }
    }
    else if (remove_from == REMOVE_NEXT) {
        if (handle->pos) {
            sl_node* temp = handle->pos->next;
            if (temp) {
                handle->pos->next = temp->next;
                free(temp);
            }
            handle->pos = NULL;
        }
    }
}

/*
 * destroy the complete list
 */
void sl_list_cleanup(sl_handle* handle)
{
    sl_node *temp = handle->front;
    while (temp != NULL) {
       handle->front = handle->front->next;
       free(temp);
       temp = handle->front;
    } 
}

/* Gives no. of elements in list */
int sl_list_size(sl_handle* handle)
{
    return (handle->list_size);
}

/* To Check if list is empty, returns 1 if empty */
bool sl_list_empty(sl_handle* handle)
{
    return ((!handle->list_size) ? 1 : 0);
}

/* Accesor Function: to iterate and retun data node by node */
int sl_list_get_next(sl_handle* handle, sl_node** move, int* data)
{
    /* *move == NULL , entering first time */
    if (*move == NULL) {
        *move = handle->front;
    }
    if (*move) { 
        *data = (*move)->key;
        *move = (*move)->next;
        /* Reached to last element of list */
        if (*move == NULL) {
            /* List is empty or iteration over */
            return (0);
        }
    }    
    return (1);
}

 /*
 * display the element with value data in the list.
 */
void sl_list_display(sl_handle* handle)
{
    int i = 1;
    int key = 0;
    sl_node* temp = handle->front;
    printf("List Start:\n");
    while (temp != NULL) {
        key = temp->key;
        printf("Element:%d , key:%d\n",i,key);
        temp = temp->next;
        i++;
    }
    printf("List End:\n");
}
