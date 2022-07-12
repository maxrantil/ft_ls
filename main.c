#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "stdbool.h"
#include <assert.h>
#include <stdio.h>
#include "libraries/includes/vec.h"
//Create a function vec_from which takes in a pointer to some memory, 
//which then will be copied over to the new vector.


int main(void)
{
   t_vec   t1;
    int     base[] = {1, 2, 3, 4, 5};

    assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
    assert(vec_resize(&t1, 100) > 0);
    assert(memcmp(t1.memory, base, sizeof(base)) == 0);
    vec_free(&t1);
	printf("test_vec_new successful!\n");
}