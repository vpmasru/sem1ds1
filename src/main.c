#include <getopt.h>

#include "common.h"
#include "queue.h"
#include "sort_list.h"

db_ctx_t g_db_ctx;
db_ctx_t *g_db_ctx_p = &g_db_ctx;


void help_msg(const char *exec_name)
{
    printf("Usage: %s [-v] [file]\n", exec_name);
}

void
add_data_record(int n)
{
    if (g_db_ctx_p->sort_en) {
        sort_list_insert(n);
    } else if (g_db_ctx_p->queue_en) {
        queue_push(n);
    } else {
        /* just print the records if no option selected */
        printf("record: %d\n", n);
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
    }
    DBG("\n");

    // Close the file
    fclose(file);

    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int rc = EXIT_SUCCESS;
    char *fname = NULL;

    while ((opt = getopt(argc, argv, "df:h")) != -1) {
        switch (opt) {
            case 'd':
                g_db_ctx_p->dbg_en = true;
                break;
            case 'f':
                g_db_ctx_p->in_mode_file_en = true;
                fname = optarg;
                break;
            case 'h':
                help_msg(argv[0]);
                exit(EXIT_SUCCESS);
                break;
            default:
                help_msg(argv[0]);
                exit(EXIT_FAILURE);
                break;
        }
    }

    // Display remaining arguments (non-option arguments)
    for (int i = optind; i < argc; i++) {
        printf("Non-option argument: %s\n", argv[i]);
        exit(EXIT_FAILURE);
    }

    // Display options
    if (g_db_ctx_p->dbg_en) {
        DBG("Debug mode is enabled.\n");
    }

    if (g_db_ctx_p->in_mode_file_en) {
        DBG("Input mode is file %s\n", fname);
        rc = read_input_file(fname);
    }

    return rc;
}
