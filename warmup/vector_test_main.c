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

int char_cmpfunc (void * a, void * b)
{
   return (*(char *)a - *(char *)b);
}

int int_cmpfunc (void * a, void * b)
{
   return (*(int *)a - *(int *)b);
}

void print_int(void *src)
{
    printf("%d ", *(int *)src);
}

void print_str(void *src)
{
    printf("%s ", (char *)src);
}

int main () {
	t_vec arr;
	t_vec arr2;
	int ret;
	int ret2;

	ret = vec_from(&arr, int_arr, 5, sizeof(int));
	if (ret < 0)
        printf("Error!");
	ret2 = vec_from(&arr2, values, 5, sizeof(values[0]));
	if (ret2 < 0)
        printf("Error!");
	printf("Before sorting the list is: \n");
	vec_iter(&arr, print_int);
	printf("\n");
	vec_iter(&arr2, print_str);

   /* for(int n = 0 ; n < 5; n++ ) {
      printf("%d ", int_arr[n]);
   } */

	vec_sort(&arr, int_cmpfunc);
	vec_sort(&arr2, char_cmpfunc);

	printf("\nAfter sorting the list is: \n");
    vec_iter(&arr, print_int);
	printf("\n");
    vec_iter(&arr2, print_str);

   /* for(int n = 0 ; n < 5; n++ ) {   
      printf("%d ", int_arr[n]);
   } */
	vec_free(&arr);
   return(0);
}