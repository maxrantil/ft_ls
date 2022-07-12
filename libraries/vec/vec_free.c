#include "../includes/vec.h"

void vec_free(t_vec *src)
{
	if (!src || src->alloc_size == 0)
		return ;
	free(src->memory);
	src->memory = NULL;
	src->elem_size = 0;
	src->alloc_size = 0;
	src->len = 0;
}
