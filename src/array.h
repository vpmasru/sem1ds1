/*
 * initialize the array with default size 
 * Array will be managed using heap memory
 */
int* array_init(void);

/*
 * Resize the array with new size given
 * which would reallocate the array from heap
 * and copy the  existing records
 */
int* array_resize(int new_size);

/*
 * add element with value data to the array back 
 * It will first search the element and
 * discard if the record already present
 */
void array_insert(int data);

/*
 * remove the front element or first entry of the array
 */
void array_remove(void);

/*
 * search the element with data value in the array
 * and return the index if found
 */
int array_search(int data);

/*
 * destroy the array and with present records
 */
void array_cleanup();

