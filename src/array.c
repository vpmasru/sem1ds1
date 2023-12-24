#include <stdlib.h>

#include "array.h"
/*
 * initialize the array with default size 
 * Array will be managed using heap memory
 */
int* array_init(void)
{
    int *mem = NULL;

    return mem;
}

/*
 * Resize the array with new size given
 * which would reallocate the array from heap
 * and copy the  existing records
 */
int* array_resize(int new_size)
{
    int *mem = NULL;

    return mem;
}

/*
 * add element with value data to the array back 
 * It will first search the element and
 * discard if the record already present
 */
void array_insert(int data)
{
    return;
}

/*
 * remove the front element or first entry of the array
 */
void array_remove(void)
{
    return;
}

/*
 * search the element with data value in the array
 * and return the index if found
 */
int array_search(int data)
{
    return 0;
}

/*
 * destroy the array and with present records
 */
void array_cleanup()
{
    return;
}

