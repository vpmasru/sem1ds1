#include <getopt.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "common.h"
#include "queue.h"
#include "list.h"
#include "sort_list.h"
#include "db.h"

db_ctx_t g_db_ctx;
db_ctx_t *g_db_ctx_p = &g_db_ctx;

#define EXEC_NAME_STR_MAX_LEN 100
char prog_name[EXEC_NAME_STR_MAX_LEN];

void help_msg()
{
    printf("Usage: %s\n", prog_name);
    
    printf(ONE_TAB "-c : cleanup the internal db files. Individual db file can be selected using s option\n");
    printf(ONE_TAB "-d : turn on debug messages\n");
    printf(ONE_TAB "-f <filename 1> ... <filname N> : input data given via files. Max input files allowed is 10\n");
    printf(ONE_TAB "-h : this help message\n");
    printf(ONE_TAB "-i <val> : insert <val> to data structure\n");
    printf(ONE_TAB "-p : dequeue first element from queue\n");
    printf(ONE_TAB "-r <val>: remove <val> from sorted linked list\n");
    printf(ONE_TAB "-s <n>:  select ADT type. <n> can be\n");
    printf(TWO_TAB "%d - queue with array\n", ADT_MODEL_QUEUE_ARRAY);
    printf(TWO_TAB "%d - queue with linked list\n", ADT_MODEL_QUEUE_LLIST);
    printf(TWO_TAB "%d - sorted linked list\n", ADT_MODEL_SORTED_LLIST);
    printf(ONE_TAB "-t : show elements of data structure in the order\n");
}

/*
 * initialise the queue or sorted list 
 */
void
adt_init(void)
{
    if (g_db_ctx_p->sort_en) {
        g_db_ctx_p->sort_list_handle_p = sort_list_init();
    } else {
        queue_init();
    }
}

/*
 * destroy the queue or sorted list 
 */
void
adt_cleanup(void)
{
    if (g_db_ctx_p->sort_en) {
        sort_list_cleanup(g_db_ctx_p->sort_list_handle_p);
    } else {
        queue_cleanup();
    }
}

struct timespec *
clock_diff (struct timespec *start, struct timespec *end, struct timespec *diff)
{
    assert(start && diff);
    struct timespec now;
    if (end == NULL) {
        clock_gettime(CLOCK_REALTIME, &now);
        end = &now;
    }
    diff->tv_sec = end->tv_sec - start->tv_sec;
    diff->tv_nsec = end->tv_nsec - start->tv_nsec;
    if (diff->tv_nsec < 0) {
        diff->tv_nsec += 1000 * 1000 * 1000;
        diff->tv_sec -= 1;
    }
    return diff;
}

struct timespec total_time;

void
clock_add (struct timespec *base, struct timespec *newts)
{
    assert(base && newts);
    base->tv_sec = base->tv_sec + newts->tv_sec;
    base->tv_nsec = base->tv_nsec + newts->tv_nsec;
    if (base->tv_nsec >= 1000 * 1000 * 1000) {
        base->tv_nsec -= 1000 * 1000 * 1000;
        base->tv_sec += 1;
    }
    return;
}

/*
 * add data entry to the queue or sorted list 
 */
void
add_data_record(int data)
{
    struct timespec start, elapsed;

    clock_gettime(CLOCK_REALTIME_COARSE, &start);
    if (g_db_ctx_p->sort_en) {
        sort_list_insert((sl_handle* )g_db_ctx_p->sort_list_handle_p, data);
    } else {
        queue_push(data);
    }
    clock_diff(&start, NULL, &elapsed);

    clock_add(&total_time, &elapsed);    
}

/*
 * delete data entry from the queue or sorted list 
 */
void
delete_data_record(int data)
{
    struct timespec start, elapsed;

    clock_gettime(CLOCK_REALTIME_COARSE, &start);
    if (g_db_ctx_p->sort_en) {
        sort_list_remove((sl_handle *)g_db_ctx_p->sort_list_handle_p, data);
    } else {
        queue_pop();
    }
    clock_diff(&start, NULL, &elapsed);

    clock_add(&total_time, &elapsed);    
}

/*
 * display data entry of the queue or sorted list 
 */
void
display_data_record(void)
{
    if (g_db_ctx_p->sort_en) {
        sort_list_display((sl_handle *)g_db_ctx_p->sort_list_handle_p);
    } else {
        queue_display();
    }
}

int read_input_file(const char *fname)
{

    // Open the file for reading
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("ERROR: opening inpu file %s\n", fname);
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

    if (!ok && !g_db_ctx_p->cleanup_db_en) {
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
        for (int i = 0; i < g_db_ctx_p->in_file_num; i++) {
            DBG("Input mode is file %s\n", g_db_ctx_p->in_fname[i]);
            rc = read_input_file(g_db_ctx_p->in_fname[i]);
        }

        if (g_db_ctx_p->file_record_size <= 0) {
            printf("ERROR: Input Files has no data\n");
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

    printf("Operation elapse time %ld sec %ld nsec\n", total_time.tv_sec, total_time.tv_nsec);
    return rc;
}

int main(int argc, char *argv[]) {
    int opt;
    int rc = EXIT_SUCCESS;
    int i, j;

    /*copy exec name*/
    strncpy(prog_name, argv[0], EXEC_NAME_STR_MAX_LEN);

    if (argc < MIN_ARGS_COUNT) {
        printf("%s: too few arguments\n", argv[0]);
        help_msg();
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "cdf:hi:pr:s:t")) != -1) {
        switch (opt) {
            case 'c':
                g_db_ctx_p->cleanup_db_en = true;
                break;

            case 'd':
                g_db_ctx_p->dbg_en = true;
                break;

            case 'f':
                g_db_ctx_p->in_mode_file_en = true;
                for (i = optind - 1, j = 0; i < argc && argv[i][0] != '-'; i++, j++) {
                    strncpy(g_db_ctx_p->in_fname[j], argv[i], INPUT_FNAME_MAX_STR_LEN);
                    if (j > INPUT_FNAME_MAX_NUM) {
                        help_msg();
                        exit(EXIT_SUCCESS);
                    }
                }
                g_db_ctx_p->in_file_num = j;
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
    for (int i = (optind + g_db_ctx_p->in_file_num); i < argc; i++) {
        printf("Non-option argument: %s\n", argv[i]);
        exit(EXIT_FAILURE);
    }

    // sanitise the command line options
    cmd_option_validate();

    // warn debug logging
    DBG("Debug mode is enabled.\n");

    if (g_db_ctx_p->cleanup_db_en) {
        cleanup_db();
        goto exit;
    }

    // initialise ADT
    adt_init();

    // construct the data structure
    read_db();

    rc = execute_operation();
    if (rc != 0) {
        goto exit;
    }

    // sync data structure to db
    write_db();

    // destroy ADT
    adt_cleanup();

exit:
    return rc;
}
