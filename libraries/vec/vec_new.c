#include "vec.h"
//Create a function vec_new which will take a pointer to a t_vec
//and allocate len * elem_size bytes in the buffer as well as
//initialize its length and element size.
int vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (!dst || elem_size == 0)
		return (-1);
	dst->alloc_size = init_len * elem_size;
	dst->len = 0;
	dst->elem_size = elem_size;
	if (init_len == 0)
		dst->memory = NULL;
	else
	{
		dst->memory = malloc(dst->alloc_size);
		if (!dst->memory)
		{
			perror("vec_new");
			exit(EXIT_FAILURE);
		}
	}
	return (dst->alloc_size);
}
