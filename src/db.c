#include "common.h"
#include "db.h"
#include "queue.h"
#include "sort_list.h"

#define FILE_DB_QUEUE_ARRAY "file_db_queue_array"
#define FILE_DB_QUEUE_LLIST "file_db_queue_llist"
#define FILE_DB_SORT_LIST "file_db_sort_list"

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

int
get_record_by_index(int index, int *record)
{
    int rc = 0;

    if (g_db_ctx_p->sort_en) {
        rc = sort_list_get_item_by_index(index, record);
    } else {
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
        add_data_record(num);
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

    index = 0;
    while (get_record_by_index(index, &record) == 0) {
        fprintf(file, "%d,", record);
        index++;
        // Process each number (in this example, just printing)
        DBG("%d ", record);
    }
    DBG("\ntotal records written %d\n", index);

    // Close the file
    fclose(file);

    return rc;
}
