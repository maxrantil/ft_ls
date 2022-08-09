#include "ft_ls.h"

void	noflag(struct dirent *dirp, const char *path)
{
	t_vec	noflag;
	DIR		*dp;
	int		ret;
	
	dp = open_path(path);
	vec_new(&noflag, 20, sizeof(dirp->d_name));
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] == '.')
			continue ;
		ret = vec_push(&noflag, dirp->d_name);
		if (ret < 0)
		{
			perror("vec_push");
			exit(EXIT_FAILURE);
		}
	}
	vec_sort(&noflag, cmpfunc_str);
	vec_iter(&noflag, print_str);
	ft_printf("\n");
	vec_free(&noflag);
	if (closedir(dp) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}