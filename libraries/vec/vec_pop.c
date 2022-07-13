#include "../includes/vec.h"
//Create a function vec_pop which will remove 
//the last element from the vector and copy it to dst.
int vec_pop(void *dst, t_vec *src)
{
	if (!dst || !src)
		return (-1);
	else if (!src->memory || src->len == 0)
		return (0);
	ft_memcpy(dst, vec_get(src, src->len - 1), src->elem_size);
	src->len--;
	return (1);
}