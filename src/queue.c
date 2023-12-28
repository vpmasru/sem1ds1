#include "common.h"
#include "queue.h"
#include "array.h"

/*
 * insert element with record data to the back of the queue
 */
void queue_push(int data)
{
    /*
     * first search the data already present.
     * if so discard it
     */
    if (queue_search(data) != -1) {
        return;
    }

    if (g_db_ctx_p->queue_arr_en) {
        array_insert(g_db_ctx_p->queue_arr_handle_p, data);
    }

    return;
}

/*
 * remove the element at the back of the queue
 */
void queue_pop(void)
{
    if (g_db_ctx_p->queue_arr_en) {
        array_remove(g_db_ctx_p->queue_arr_handle_p);
    }
}

/*
 * return the number of records in the queue
 */
int queue_size(void)
{
    return 0;
}

/*
 * return the first element of the queue
 */
int queue_front(void)
{
    return 0;
}
/*
 * return last element of the queue 
 */
int queue_back(void)
{
    return 0;
}

/*
 * fetch the queue entry stored at index 
 */
int
queue_get_item_by_index(int index, int *data)
{
    int rc = 0;

    if (g_db_ctx_p->queue_arr_en) {
        array_get_item_by_index(g_db_ctx_p->queue_arr_handle_p, index, data);
    }

    return rc;
}

/*
 * search given data in the queue
 * return the index of the data in the queue.
 */
int queue_search(int data)
{
    int index = -1;

    if (g_db_ctx_p->queue_arr_en) {
        index = array_search(g_db_ctx_p->queue_arr_handle_p, data);
    }

    return index;
}

/*
 * traverse all items of the queue and display the elements
 */
void queue_display(void)
{
    if (g_db_ctx_p->queue_arr_en) {
        array_display(g_db_ctx_p->queue_arr_handle_p);
    }
}

/*
 * initialise the queue internals
 */
void queue_init(void)
{
    if (g_db_ctx_p->queue_arr_en) {
        g_db_ctx_p->queue_arr_handle_p = array_init();
    }
}

/*
 * cleanup the queue internals
 */
void queue_cleanup(void)
{
    if (g_db_ctx_p->queue_arr_en) {
        array_cleanup(g_db_ctx_p->queue_arr_handle_p);
    }
}

