#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "array.h"
#include "common.h"

queue_array_handle q_arr_hdl;

/*
 * initialize the array with default size 
 * Array will be managed using heap memory
 */
queue_array_handle* array_init(void)
{
    queue_array_handle *q_arr = &q_arr_hdl;

    q_arr->front = -1;
    q_arr->rear = -1;
    q_arr->item_size = 0;
    q_arr->arr_size = QUEUE_ARRAY_CHUNK_SIZE;

    q_arr->arr = (int *) calloc(q_arr->arr_size, sizeof(int));
    if (!q_arr->arr) {
        printf("ERROR: array_init: alloc failure\n");
        exit(EXIT_FAILURE);
    }

    return q_arr;
}

/*
 * Resize the array with new size given
 * which would reallocate the array from heap
 * and copy the  existing records
 */
void array_resize(queue_array_handle *q_arr)
{
    int old_size = q_arr->arr_size;
    q_arr->arr_size *= 2;
    q_arr->arr = (int *) reallocarray(q_arr->arr, q_arr->arr_size, sizeof(int));
    if (!q_arr->arr) {
        printf("ERROR: array_resize: alloc failure\n");
        exit(EXIT_FAILURE);
    }

    if (q_arr->front > q_arr->rear) {
        for (int i = 0; i < q_arr->front; i++) {
            q_arr->arr[i + old_size] = q_arr->arr[i];
        }
        q_arr->rear = q_arr->rear + old_size;
    }

    return;
}

/*
 * destroy the array and with present records
 */
void array_cleanup(queue_array_handle *q_arr)
{
    free(q_arr->arr);
    q_arr->arr = NULL;
    q_arr->front = -1;
    q_arr->rear = -1;
    q_arr->item_size = 0;

    return;
}

bool is_array_full(queue_array_handle *q_arr)
{
    return (q_arr->item_size < q_arr->arr_size) ? false : true; 
}

bool is_array_empty(queue_array_handle *q_arr)
{
    return (q_arr->item_size == 0) ? true : false;
}

/*
 * add element with value data to the array back 
 * It will first search the element and
 * discard if the record already present
 */
void array_insert(queue_array_handle *q_arr, int data)
{
    if (is_array_full(q_arr)) {
        array_resize(q_arr);
    }

    if (is_array_empty(q_arr)) {
        // If the queue is empty, set front and rear to 0
        q_arr->front = 0;
        q_arr->rear = 0;
    } else {
        // Increment the rear index in a circular fashion
        q_arr->rear = (q_arr->rear + 1) % q_arr->arr_size;
    }

    // Enqueue the element
    q_arr->arr[q_arr->rear] = data;

    q_arr->item_size++;
    return;
}

/*
 * remove the front element or first entry of the array
 */
int array_remove(queue_array_handle *q_arr)
{
    int data;

    if (is_array_empty(q_arr)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Return a special value indicating an error
    } else if (q_arr->front == q_arr->rear) {
        // If there is only one element in the queue, reset front and rear to -1
        data = q_arr->arr[q_arr->front];
        q_arr->front = -1;
        q_arr->rear = -1;
    } else {
        // Dequeue the element and increment the front index in a circular fashion
        data = q_arr->arr[q_arr->front];
        q_arr->front = (q_arr->front + 1) % q_arr->arr_size;
    }

    q_arr->item_size--;

    return data;
}

/*
 * search the element with data value in the array
 * and return the index if found
 */
int array_search(queue_array_handle *q_arr, int data)
{
    int i;

    if (is_array_empty(q_arr)) {
        DBG("array_search: Queue is empty.\n");
        return -1;
    }

    for (i = q_arr->front;
            (i != (q_arr->rear + 1) % q_arr->arr_size);
            (i = (i + 1) % q_arr->arr_size)) {
        if (data == q_arr->arr[i]) {
            return i;
        }
    }

    return -1;
}

/*
 * print all the elements of array queue
 */
void array_display(queue_array_handle *q_arr)
{
    int i;

    if (is_array_empty(q_arr)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue Array elements: \n");

    for (i = q_arr->front;
            (i != (q_arr->rear + 1) % q_arr->arr_size);
            (i = (i + 1) % q_arr->arr_size)) {
        printf("%d ", q_arr->arr[i]);
    }

    printf("\n");
}

/*
 * get the element stored at the index of the array given
 * Return error code or 0 as success
 */
int array_get_item_by_index(queue_array_handle *q_arr, int index, int *data)
{
    int arr_index;

    if ((index < 0) || (index >= q_arr->item_size)) {
        return ERANGE;
    }

    arr_index = (q_arr->front + index) % q_arr->arr_size;

    *data = q_arr->arr[arr_index];

    return 0;
}
