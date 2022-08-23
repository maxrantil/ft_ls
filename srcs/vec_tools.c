#include "ft_ls.h"

static int	sort_str_asc(void *a, void *b)
{
	return (ft_strcmp((char *)a, (const char *)b));
}

static int	sort_str_desc(void *a, void *b)
{
	return (ft_strcmp((char *)b, (const char *)a));
}

void	print_str(void *src)
{
    ft_printf("%-*s", ft_strlen((char *)src) + 2, (char *)src);
}

void	sort_it(t_vec *vec_to_sort, unsigned int bit_str)
{
	if ((bit_str & R) != 0)
		vec_sort(vec_to_sort, sort_str_desc);
	else
		vec_sort(vec_to_sort, sort_str_asc);
}