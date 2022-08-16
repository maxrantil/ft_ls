#include "ft_ls.h"

void	noflag(struct dirent *dirp, const char *path)
{
	t_vec	noflag;
	DIR		*dp;
	
	dp = open_path(path);
	if (!dp)
		return ;
	vec_new(&noflag, 20, sizeof(dirp->d_name));
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] == '.')
			continue ;
		if (vec_push(&noflag, dirp->d_name) < 0)
		{
			perror("vec_push");
			exit(1);
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