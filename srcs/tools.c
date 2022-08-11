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

/* static char* print_no_path(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	while (s[len] != '/')
		len--;
	return (&s[++len]);
} */

void print_stat(void *src)
{
	struct stat	statbuf;
	//char		*no_path;			
	
	if (!stat((const char *)src, &statbuf))
	{
		print_file_props(statbuf);
	//	no_path = print_no_path((char *)src);
	//	ft_printf("%s\n", no_path);
		ft_printf("%s\n", (char *)src);
	}
	else
	{
		perror("stat in print_stat");
		exit(1);
	}
}

size_t count_files(char *dir_name)
{
	struct dirent	*dirp;
	DIR				*dp;
	size_t			file_count;

	file_count = 0;
	dp = open_path(dir_name);
	while ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strcmp(dirp->d_name, ".") == 0 || ft_strcmp(dirp->d_name, "..") == 0)
			continue ;
		++file_count;
	}
	free(dirp);
	free(dp);
	return (file_count);
}