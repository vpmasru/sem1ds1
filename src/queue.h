#ifndef _QUEUE_H_
#define _QUEUE_H_

/*
 * insert element with record data to the back of the queue
 */
void queue_push(int data);

/*
 * remove the element at the back of the queue
 */
void queue_pop(void);

/*
 * return the number of records in the queue
 */
int queue_size(void);

/*
 * return the first element of the queue
 */
int queue_front(void);
/*
 * return last element of the queue 
 */
int queue_rear(void);
/*
 * fetch the queue entry stored at index 
 */
int queue_get_item_by_index(int index, int *record);

#endif /*_QUEUE_H_*/
