#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static sl_node* front;
static sl_node* rear;
static int list_size;
/*
 * Initialize the list
 */
void sl_list_init()
{
    front = NULL;
    rear = NULL;
    list_size = 0;
}

/*
 * search the element with data value in the list and
 * return node if found.
 */
sl_node* sl_list_search(int key)
{
   sl_node* temp = front;
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
 * mode = 1 , insert from front.
 * mode = 2 , insert from rear.
 */
int sl_list_push(int key, char insert_from)
{
    sl_node* temp = NULL; 
    temp = malloc(sizeof(sl_node));
    if (temp == NULL) {
        /* Heap exhausted */
        printf("sl_list_push failed to alloc memory\n");
        return LIST_ERROR;
    }
    temp->key = key;
    /* Incase list is empty make sure head=rear=first element */
    if (sl_list_empty()) {
        front = rear = temp;
    }
    else {
        /* Add from rear */
        if ( insert_from == INSERT_REAR) {
            rear->next = temp;
            rear = temp;
        }
        else {
            /* add from front */
            temp->next = front;
            front = temp;
        } 
    }
    list_size++;
    return (0);
}


/*
 * remove the element with value data to the list
 * mode = 1 , remove from front.
 * mode = 2 , remove from rear.
 */
void sl_list_pop(char remove_from)
{
    if ((front != NULL) && (remove_from == REMOVE_FRONT)) {
        sl_node* temp = front;
        front = front->next;
        free(temp);
        list_size--;
        if (front == NULL) {
            rear = NULL;
        }
    }
    else if ((rear != NULL) && (remove_from == REMOVE_REAR)) {
        /* TBD: implement if needed */
    }
}

/*
 * destroy the complete list
 */
void sl_list_cleanup()
{
    while (front != NULL) {
        sl_list_pop(REMOVE_FRONT);
    } 
}

/* Gives no. of elements in list */
int sl_list_size()
{
    return (list_size);
}

/* To Check if list is empty, returns 1 if empty */
bool sl_list_empty()
{
    return ((!list_size) ? 1 : 0);
}

 /*
 * display the element with value data in the list.
 */
void sl_list_display()
{
    int i = 1;
    int key = 0;
    sl_node* temp = front;
    printf("List Start:\n");
    while (temp != NULL) {
        key = temp->key;
        printf("Element:%d , key:%d\n",i,key);
        temp = temp->next;
        i++;
    }
    printf("List End:\n");
}
