#include "ft_ls.h"

static void	flag_null(t_ls *utils, size_t i)
{
	t_vec	v_files;
	
	vec_new(&v_files, 20, MAX_FILENAME);
	while ((utils->dirp = readdir(utils->dp[i])) != NULL)
	{
		if (utils->bit_flags ^ A && utils->dirp->d_name[0] == '.')
			continue ;
		if (vec_push(&v_files, utils->dirp->d_name) < 0)
		{
			perror("vec_push, flag_null");
			exit(1);
		}
	}
	vec_sort(&v_files, cmpfunc_str);
	print_files(utils, &v_files, i);
	vec_free(&v_files);
	if (closedir(utils->dp[i]) < 0)
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
		flag_null(utils, i);
	else
		vec_sort(&utils->v_paths, cmpfunc_str);
	size_t j = 0;
	while (i < utils->v_paths.len)
	{
		while (j < utils->v_paths.len)
		{
			utils->dp[j] = open_path((char *)vec_get(&utils->v_paths, j));
			j++;
		}
		if (utils->dp[i])
			flag_null(utils, i);
		i++;
	}
}