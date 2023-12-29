#include "common.h"
#include "queue.h"
#include "array.h"
#include "list.h"

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
        DBG("WARN: duplicate data %d discarded\n", data);
        return;
    }

    if (g_db_ctx_p->queue_arr_en) {
        array_insert(g_db_ctx_p->queue_arr_handle_p, data);
    }
    if (g_db_ctx_p->queue_list_en) {
        sl_list_push(g_db_ctx_p->queue_list_handle_p, data, INSERT_REAR);
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
    if (g_db_ctx_p->queue_list_en) {
        sl_list_pop(g_db_ctx_p->queue_list_handle_p, REMOVE_FRONT);
    }
}

/*
 * return the number of records in the queue
 */
int queue_size(void)
{
    if (g_db_ctx_p->queue_list_en) {
        return (sl_list_size(g_db_ctx_p->queue_list_handle_p));
    }
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
 * return error code in case of error, else return 0
 */
int
queue_get_item_by_index(int index, int *data)
{
    int rc = 0;

    if (g_db_ctx_p->queue_arr_en) {
        rc = array_get_item_by_index(g_db_ctx_p->queue_arr_handle_p, index, data);
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
    void *ptr = NULL;
    if (g_db_ctx_p->queue_arr_en) {
        index = array_search(g_db_ctx_p->queue_arr_handle_p, data);
        return index;
    }
    if (g_db_ctx_p->queue_list_en) {
        ptr = sl_list_search(g_db_ctx_p->queue_list_handle_p, data);
        if (ptr) {
            return (1);
        }
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
    if (g_db_ctx_p->queue_list_en) {
        sl_list_display(g_db_ctx_p->queue_list_handle_p);
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
    if (g_db_ctx_p->queue_list_en) {
        g_db_ctx_p->queue_list_handle_p = sl_list_init(0);
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
    if (g_db_ctx_p->queue_list_en) {
        sl_list_cleanup(g_db_ctx_p->queue_list_handle_p);
    }
}

