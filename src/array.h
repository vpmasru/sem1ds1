#ifndef _ARRAY_H_
#define _ARRAY_H_

#define QUEUE_ARRAY_CHUNK_SIZE 1000

/*
 * Structure for the FIFO queue
 */
typedef struct {
    int *arr;
    int front;
    int rear;
    int arr_size;
    int item_size;
} queue_array_handle;

/*
 * initialize the array with default size 
 * Array will be managed using heap memory
 */
queue_array_handle* array_init(void);

/*
 * Resize the array with new size given
 * which would reallocate the array from heap
 * and copy the  existing records
 */
void array_resize(queue_array_handle *q_arr);

/*
 * destroy the array and with present records
 */
void array_cleanup(queue_array_handle *q_arr);

/*
 * add element with value data to the array back 
 * It will first search the element and
 * discard if the record already present
 */
void array_insert(queue_array_handle *q_arr, int data);

/*
 * remove the front element or first entry of the array
 */
int array_remove(queue_array_handle *q_arr);

/*
 * search the element with data value in the array
 * and return the index if found
 */
int array_search(queue_array_handle *q_arr, int data);

/*
 * print all the elements of array queue
 */
void array_display(queue_array_handle *q_arr);

/*
 * get the element stored at the index of the array given  
 */
int array_get_item_by_index(queue_array_handle *q_arr, int index, int *data);
#endif /* _ARRAY_H_ */

