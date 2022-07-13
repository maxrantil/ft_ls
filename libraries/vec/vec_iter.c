#include "vec.h"

void vec_iter(t_vec *src, void (*f) (void *))
{
	void	*ptr;
	size_t	i;

	if (!src || !src->memory)
		return ;
	i = 0;
	while (i < src->len)
	{
		ptr = vec_get(src, i);
		f(ptr);
		i++;
	}
}