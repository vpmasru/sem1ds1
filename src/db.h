
#ifndef _DB_H_
#define _DB_H_

#define FILE_DB_QUEUE_ARRAY "file_db_queue_array"
#define FILE_DB_QUEUE_LLIST "file_db_queue_llist"
#define FILE_DB_SORT_LIST "file_db_sort_list"

/*
 * read the DB file and reconstruct the data structure from DB 
 */
int read_db(void);

/*
 * sync the data structure to DB file after the operation
 */
int write_db(void);

#endif /*_DB_H_*/
