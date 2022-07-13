#include "../includes/vec.h"

int vec_clear(t_vec *src)
{
	if (!src)
		return (-1);
	src->len = 0;
	return (1);
}