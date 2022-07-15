#include "ft_ls.h"

DIR*	open_path(const char *str)
{
	DIR *dp;
	
	dp = opendir(str);
	if (!dp)
	{
		perror("open_path");
		exit(EXIT_FAILURE);
	}
	return (dp);
}

int cmpfunc_str(void *a, void *b)
{
	int	ret;
	
	ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	while (*(char *)a && *(char *)b && !ret)
	{
		((*(char *)&a)++);
		((*(char *)&b)++);
		ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	}
	return (ret);
}

void print_str(void *src)
{
	ft_printf("%-*s ", ft_strlen((char *)src) + 1, (char *)src);
}