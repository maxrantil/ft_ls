#include "vec.h"
//Create a function that frees the allocated resources in src and zeroes its fields.
void vec_free(t_vec *src)
{
	if (!src || src->alloc_size == 0)
		return ;
	ft_memdel((void *)&src->memory);
	src->elem_size = 0;
	src->alloc_size = 0;
	src->len = 0;
}
