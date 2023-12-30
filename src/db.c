#include "common.h"
#include "db.h"
#include "queue.h"
#include "list.h"
#include "sort_list.h"

const char *
get_db_filename(void)
{
    if (g_db_ctx_p->sort_en) {
        return FILE_DB_SORT_LIST;
    } else if (g_db_ctx_p->queue_arr_en) {
        return FILE_DB_QUEUE_ARRAY;
    } else {
        return FILE_DB_QUEUE_LLIST;
    }
}

void cleanup_db(void)
{
    if (g_db_ctx_p->sort_en) {
        remove(FILE_DB_SORT_LIST);
    } else if (g_db_ctx_p->queue_arr_en) {
        remove(FILE_DB_QUEUE_ARRAY);
    } else if (g_db_ctx_p->queue_list_en) {
        remove(FILE_DB_QUEUE_LLIST);
    } else {
        /* default remove all db files */
        remove(FILE_DB_SORT_LIST);
        remove(FILE_DB_QUEUE_ARRAY);
        remove(FILE_DB_QUEUE_LLIST);
    }
}

/*
 * add data entry to the queue or sorted list from db
 */
void
db_add_data_record(int data)
{
    if (g_db_ctx_p->sort_en) {
        sort_list_insert((sl_handle* )g_db_ctx_p->sort_list_handle_p, data);
    } else {
        queue_push(data);
    }
}

int
get_record_by_index(int index, int *record)
{
    int rc = 0;
    if (g_db_ctx_p->queue_arr_en) {
        rc = queue_get_item_by_index(index, record);
    }

    return rc;
}

/*
 * read the DB file and reconstruct the data structure from DB 
 */
int read_db(void)
{
    int rc = 0;
    const char *fname = NULL;

    fname = get_db_filename();
    if (!fname) {
        return EINVAL;
    }

    // Open the file for reading
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        DBG("file %s is empty\n", fname);
        return rc;
    }

    // Read numbers from the file
    int num;
    while (fscanf(file, "%d%*[, \t\n]", &num) == 1) {
        // Process each number (in this example, just printing)
        DBG("%d ", num);
        db_add_data_record(num);
        g_db_ctx_p->db_record_size++;
    }
    DBG("\ntotal records %d\n", g_db_ctx_p->db_record_size);

    // Close the file
    fclose(file);

    return rc;
}

/*
 * sync the data structure to DB file after the operation
 */
int write_db(void)
{
    int rc = 0;
    const char *fname = NULL;
    int index;
    int record;

    fname = get_db_filename();
    if (!fname) {
        return EINVAL;
    }

    // Open the file for writing
    FILE *file = fopen(fname, "w");
    if (file == NULL) {
        printf("ERROR: file %s open failed\n", fname);
        return rc;
    }

    if (g_db_ctx_p->queue_arr_en) {
        index = 0;
        while (get_record_by_index(index, &record) == 0) {
            fprintf(file, "%d,", record);
            index++;
            // Process each number (in this example, just printing)
            DBG("%d ", record);
        }
    }
    else {
        int loop = 1;
        index = 0;
        void *handle = NULL;
        sl_node *temp = NULL;

        if (g_db_ctx_p->queue_list_en) {
            handle = g_db_ctx_p->queue_list_handle_p;
        }
        else {
            handle = g_db_ctx_p->sort_list_handle_p;
        }

        if (!sl_list_empty(handle)) {
            while(loop) {
                loop = sl_list_get_next(handle, &temp, &record);
                fprintf(file, "%d,", record);
                index++; 
                // Process each number (in this example, just printing)
                DBG("%d ", record);
            };
        }
    }
    DBG("\ntotal records written %d\n", index);

    // Close the file
    fclose(file);

    return rc;
}
