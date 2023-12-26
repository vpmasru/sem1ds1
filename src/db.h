
#ifndef _DB_H_
#define _DB_H_
/*
 * read the DB file and reconstruct the data structure from DB 
 */
int read_db(void);

/*
 * sync the data structure to DB file after the operation
 */
int write_db(void);

#endif /*_DB_H_*/
