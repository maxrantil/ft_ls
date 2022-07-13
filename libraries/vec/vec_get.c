#include "../includes/vec.h"
//Create a function vec_get which returns an opaque handle to the element at index.
void *vec_get(t_vec *src, size_t index)
{
	unsigned char	*ptr;

	if (index >= src->len || !src || !src->memory)
		return (NULL);
	ptr = &src->memory[src->elem_size * index];
	return (ptr);
}
