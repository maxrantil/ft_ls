#include "ft_ls.h"

DIR*	open_path(const char *str)
{
	DIR *dp;
	
	dp = opendir(str);
	if (!dp)
	{
		perror("open_path");
		exit(1);
	}
	return (dp);
}

int cmpfunc_str(void *a, void *b)
{
	int	ret;
	
	//need to sort correct when _ or other spcial chars is involved
	/* while (!ft_isalpha(*(char *)a))
		((*(char *)a)++);
	while (!ft_isalpha(*(char *)b))
		((*(char *)b)++); */
	ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	while (!ret && *(char *)a && *(char *)b)
	{
		((*(char *)&a)++);
		((*(char *)&b)++);
		ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	}
	return (ret);
}

void print_str(void *src)
{
	static size_t	len_count;
	size_t			win_size;

	win_size = window_size();
	len_count += ft_strlen((char *)src) + 2;
	if (len_count > win_size)
	{
		ft_putchar('\n');
		len_count = 0;
	}
	else
    	ft_printf("%-*s", ft_strlen((char *)src) + 2, (char *)src);
}