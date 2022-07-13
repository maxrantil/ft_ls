#include "ft_ls.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define NUM_STRINGS 10

unsigned char values[NUM_STRINGS][MAX_LENGTH] = { {"eeee"},
										{"dddddddd"},
										{"cccc"},
										{"bbbb"},
										{"aaaa"} };

int int_arr[] = {5, 4, 2, 3, 1};

int char_cmpfunc (void * a, void * b) {
   return ( *(char *)a - *(char *)b );
}

int int_cmpfunc (void * a, void * b) {
   return ( *(int *)a - *(int *)b );
}

void print_int(void *src)
{
    printf("%d ", *(int *)src);
}

int main () {
	t_vec arr;
	int ret;

	ret = vec_from(&arr, int_arr, 5, sizeof(int));
	if (ret < 0)
        printf("Error!");
	printf("Before sorting the list is: \n");
	vec_iter(&arr, print_int);

   /* for(int n = 0 ; n < 5; n++ ) {
      printf("%d ", int_arr[n]);
   } */

	vec_sort(&arr, int_cmpfunc);

	printf("\nAfter sorting the list is: \n");
    vec_iter(&arr, print_int);

   /* for(int n = 0 ; n < 5; n++ ) {   
      printf("%d ", int_arr[n]);
   } */
	vec_free(&arr);
   return(0);
}