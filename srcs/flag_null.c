#include "ft_ls.h"

static void	flag_null(t_ls *utils, const char *path)
{
	t_vec	v_flag_null;
	DIR		*dp;
	
	dp = open_path(path);
	if (!dp)
		return ;
	vec_new(&v_flag_null, 20, MAX_FILE);
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (utils->bit_flags ^ A && utils->dirp->d_name[0] == '.')
			continue ;
		if (vec_push(&v_flag_null, utils->dirp->d_name) < 0)
		{
			perror("vec_push, flag_null");
			exit(1);
		}
	}
	vec_sort(&v_flag_null, cmpfunc_str);
	vec_iter(&v_flag_null, print_str);
	ft_printf("\n");
	vec_free(&v_flag_null);
	if (closedir(dp) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}

void	exec_flag_null(t_ls *utils)
{
	size_t i;

	i = 0;
	if (!utils->v_paths.len)
		flag_null(utils, ".");
	else
		vec_sort(&utils->v_paths, cmpfunc_str);
	while (i < utils->v_paths.len)
	{
		if (utils->v_paths.len != 1)
			ft_printf("%s: \n", (char *)vec_get(&utils->v_paths, i));
		flag_null(utils, (char *)vec_get(&utils->v_paths, i++));
		if (i != utils->v_paths.len)
			write(1, "\n", 1);
	}
}