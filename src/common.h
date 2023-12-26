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

typedef struct db_ctx_ {
    bool sort_en;
    bool queue_en;
    bool in_mode_file_en;
    bool dbg_en;

    int record_size;
    char *in_fname;
} db_ctx_t;

extern db_ctx_t *g_db_ctx_p;

/*
 * add data entry to the queue or sorted list 
 */
void add_data_record(int n);

#endif  /*_COMMON_H_*/
