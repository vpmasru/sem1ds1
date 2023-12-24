/*
 * Initialize the list
 */
void list_init(void);

/*
 * search the element with data value in the list and
 * return the index if found
 */
int list_search(int data);

/*
 * Insert the element with value data to the list
 */
void list_insert(int data);

/*
 * search for the element with value data in the list
 * and remove the element
 */
void list_remove(int data);

/*
 * remove the last element of the list
 */
void list_pop(void);

/*
 * destroy the complete list
 */
void list_cleanup(void);

