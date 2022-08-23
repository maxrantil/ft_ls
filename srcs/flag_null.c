#include "ft_ls.h"

static void	exec_flag_null(t_ls *utils, size_t i)
{
	t_vec	v_files;
	
	vec_new(&v_files, 0, MAX_FILENAME);
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
	sort_it(&v_files, utils->bit_flags);
	print_files(utils, &v_files, i);
	vec_free(&v_files);
	/* if (closedir(utils->dp[i]) < 0)
	{
		perror("can't close directory");
		exit(1);
	} */
}

void	flag_null(t_ls *utils)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!utils->v_paths.len)
		exec_flag_null(utils, i);
	else
		sort_it(&utils->v_paths, utils->bit_flags);
	while (i < utils->v_paths.len)
	{
		while (j < utils->v_paths.len)
		{
			utils->dp[j] = open_path(utils, j);
			j++;
		}
		if (utils->dp[i])
			exec_flag_null(utils, i);
		i++;
	}
}