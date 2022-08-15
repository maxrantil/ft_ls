#include "vec.h"

/*
// Create a function which returns an opaque handle to the element at index.
*/

void *vec_get(t_vec *src, size_t index)
{
	if (index >= src->len || !src || !src->memory)
		return (NULL);
	return ((void *)&src->memory[src->elem_size * index]);
}
