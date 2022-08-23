#include "ft_ls.h"

/* int cmpfunc_str(void *a, void *b)
{
	int	ret;
	
	//need to sort correct when _ or other spcial chars is involved
	ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	while (!ret && *(char *)a && *(char *)b)
	{
		((*(char *)&a)++);
		((*(char *)&b)++);
		ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	}
	return (ret);
} */
int cmpfunc_str(void *a, void *b)
{
	return (ft_strcmp((char *)a, (const char *)b));
}


void print_str(void *src)
{
    ft_printf("%-*s", ft_strlen((char *)src) + 2, (char *)src);
}