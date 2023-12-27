#include <getopt.h>
#include <string.h>

#include "common.h"
#include "queue.h"
#include "sort_list.h"
#include "db.h"

db_ctx_t g_db_ctx;
db_ctx_t *g_db_ctx_p = &g_db_ctx;

#define EXEC_NAME_STR_MAX_LEN 100
char prog_name[EXEC_NAME_STR_MAX_LEN];

void help_msg()
{
    printf("Usage: %s\n", prog_name);
    
    printf(ONE_TAB "-d : turn on debug messages\n");
    printf(ONE_TAB "-f <filename> : input data given via files\n");
    printf(ONE_TAB "-h : this help message\n");
    printf(ONE_TAB "-i <val> : insert <val> to data structure\n");
    printf(ONE_TAB "-p : pop first element from queue\n");
    printf(ONE_TAB "-r <val>: remove <val> from sorted linked list\n");
    printf(ONE_TAB "-s <n>:  select ADT type. <n> can be\n");
    printf(TWO_TAB "%d - queue with array\n", ADT_MODEL_QUEUE_ARRAY);
    printf(TWO_TAB "%d - queue with linked list\n", ADT_MODEL_QUEUE_LLIST);
    printf(TWO_TAB "%d - sorted linked list\n", ADT_MODEL_SORTED_LLIST);
    printf(ONE_TAB "-t : show elements of data structure in the order\n");
}

/*
 * add data entry to the queue or sorted list 
 */
void
add_data_record(int data)
{
    if (g_db_ctx_p->sort_en) {
        sort_list_insert(data);
    } else {
        queue_push(data);
    }

}

/*
 * delete data entry from the queue or sorted list 
 */
void
delete_data_record(int data)
{
    if (g_db_ctx_p->sort_en) {
        sort_list_remove(data);
    } else {
        queue_pop();
    }
}

/*
 * display data entry of the queue or sorted list 
 */
void
display_data_record(void)
{
    if (g_db_ctx_p->sort_en) {
        sort_list_display();
    } else {
        queue_display();
    }
}

int read_input_file(const char *fname)
{

    // Open the file for reading
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read numbers from the file
    int num;
    while (fscanf(file, "%d%*[, \t\n]", &num) == 1) {
        // Process each number (in this example, just printing)
        DBG("%d ", num);
        add_data_record(num);
        g_db_ctx_p->file_record_size++;
    }
    DBG("\ntotal records %d\n", g_db_ctx_p->file_record_size);

    // Close the file
    fclose(file);

    return 0;
}

void cmd_option_validate(void)
{
    bool ok = true;

    /* ADT type validation */
    if ((g_db_ctx_p->adt_model != ADT_MODEL_QUEUE_ARRAY)
            && (g_db_ctx_p->adt_model != ADT_MODEL_QUEUE_LLIST)
            && (g_db_ctx_p->adt_model != ADT_MODEL_SORTED_LLIST)) {
        ok = false;
    } else {
        if (g_db_ctx_p->adt_model == ADT_MODEL_QUEUE_ARRAY) {
            g_db_ctx_p->queue_arr_en = true;
        } else if (g_db_ctx_p->adt_model == ADT_MODEL_QUEUE_LLIST) {
            g_db_ctx_p->queue_list_en = true;
        } else {
            g_db_ctx_p->sort_en = true;
        }

    }

    if (!ok) {
        help_msg();
        exit(EXIT_FAILURE);
    }
}

int
execute_operation(void)
{
    int rc = 0;

    /* read input from file */
    // TODO: read from multiple input files
    if (g_db_ctx_p->in_mode_file_en) {
        char *fname =  g_db_ctx_p->in_fname;
        DBG("Input mode is file %s\n", fname);
        rc = read_input_file(fname);

        if (g_db_ctx_p->file_record_size <= 0) {
            printf("File %s has no data\n", fname);
            return ENOTSUP;
        }

    } else if (g_db_ctx_p->insert_single_elem_en) {
        add_data_record(g_db_ctx_p->insert_single_elem);
    } else if (g_db_ctx_p->queue_pop_en
            || g_db_ctx_p->sort_list_remove_en) {
        // queue pop will discard the remove_elem item
        delete_data_record(g_db_ctx_p->sort_list_remove_elem);
    } else if (g_db_ctx_p->adt_display_en) {
        display_data_record();
    }

    return rc;
}

int main(int argc, char *argv[]) {
    int opt;
    int rc = EXIT_SUCCESS;

    /*copy exec name*/
    strncpy(prog_name, argv[0], EXEC_NAME_STR_MAX_LEN);

    if (argc < MIN_ARGS_COUNT) {
        printf("%s: too few arguments\n", argv[0]);
        help_msg();
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "df:hi:pr:s:t")) != -1) {
        switch (opt) {
            case 'd':
                g_db_ctx_p->dbg_en = true;
                break;

            case 'f':
                g_db_ctx_p->in_mode_file_en = true;
                g_db_ctx_p->in_fname = optarg;
                break;

            case 'h':
                help_msg();
                exit(EXIT_SUCCESS);
                break;

            case 'i':
                g_db_ctx_p->insert_single_elem_en = true;
                g_db_ctx_p->insert_single_elem = atoi(optarg);
                break;

            case 'p':
                g_db_ctx_p->queue_pop_en = true;
                break;

            case 'r':
                g_db_ctx_p->sort_list_remove_en = true;
                g_db_ctx_p->sort_list_remove_elem = atoi(optarg);
                break;

            case 's':
                g_db_ctx_p->adt_model = atoi(optarg);
                break;

            case 't':
                g_db_ctx_p->adt_display_en = true;
                break;

            default:
                help_msg();
                exit(EXIT_FAILURE);
                break;
        }
    }

    // Display remaining arguments (non-option arguments)
    for (int i = optind; i < argc; i++) {
        printf("Non-option argument: %s\n", argv[i]);
        exit(EXIT_FAILURE);
    }

    // sanitise the command line options
    cmd_option_validate();

    // warn debug logging
    DBG("Debug mode is enabled.\n");

    // construct the data structure
    read_db();

    rc = execute_operation();
    if (rc != 0) {
        goto exit;
    }

    // sync data structure to db
    write_db();

exit:
    return rc;
}
