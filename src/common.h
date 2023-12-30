#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

/*
 * Logging:
 */
#define DBG(...) do {               \
    if (g_db_ctx_p->dbg_en) {       \
        printf(__VA_ARGS__);        \
    }                               \
} while (0)

#define MIN_ARGS_COUNT 2
#define ONE_TAB "\t"
#define TWO_TAB "\t\t"

/* IDT data structure types */
#define ADT_MODEL_QUEUE_ARRAY   1
#define ADT_MODEL_QUEUE_LLIST   2
#define ADT_MODEL_SORTED_LLIST  3

#define INPUT_FNAME_MAX_NUM 10
#define INPUT_FNAME_MAX_STR_LEN 100
/*
 * global struct to store the different cmd options and idt handles
 */
typedef struct db_ctx_ {
    bool sort_en;
    bool queue_arr_en;
    bool queue_list_en;
    bool in_mode_file_en;
    bool dbg_en;
    bool insert_single_elem_en;
    bool queue_pop_en;
    bool sort_list_remove_en;
    bool adt_display_en;
    bool cleanup_db_en;

    int insert_single_elem;
    int sort_list_remove_elem;

    int adt_model;
    int file_record_size;
    int in_file_num;
    char in_fname[INPUT_FNAME_MAX_NUM][INPUT_FNAME_MAX_STR_LEN];
    int db_record_size;

    void *queue_arr_handle_p;
    void *queue_list_handle_p;
    void *sort_list_handle_p;
} db_ctx_t;

extern db_ctx_t *g_db_ctx_p;

/*
 * add data entry to the queue or sorted list 
 */
void add_data_record(int n);

/*
 * remove data entry from the queue or sorted list 
 */
void delete_data_record(int n);

#endif  /*_COMMON_H_*/
