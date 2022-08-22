#include "ft_ls.h"

static void	turn_on_bit_flags(t_ls *utils, char *flags)
{
	int	i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == 'a')
			utils->bit_flags |= 1;
		if (flags[i] == 'l')
			utils->bit_flags |= 2;
		if (flags[i] == 'r')
			utils->bit_flags |= 4;
		if (flags[i] == 'R')
			utils->bit_flags |= 8;
		if (flags[i] == 't')
			utils->bit_flags |= 16;
		i++;
	}
	ft_strdel(&flags);
}

static void	malloc_directory_ptr(t_ls *utils)
{
	if (!utils->v_paths.len)
	{
		utils->dp = (DIR **)malloc(sizeof(DIR *) * 1);
		utils->dp[0] = opendir(".");
	}
	else
		utils->dp = (DIR **)malloc(sizeof(DIR *) * utils->v_paths.len);
}

static void	exec_flags(t_ls *utils)
{
	if ((utils->bit_flags & CAPITAL_R) != 0)
		flag_recurse(utils);
	else if((utils->bit_flags & L) != 0)
		flag_l(utils);
	else
		flag_null(utils);
}

void	work_data(t_ls *utils, char *flags)
{
	turn_on_bit_flags(utils, flags);
	malloc_directory_ptr(utils);
	exec_flags(utils);

	vec_free(&utils->v_paths);
	ssize_t i = utils->v_paths.len; // lean up this into another function?? or place it right after it is beeing used
	while (i >= 0)
	{
		free(utils->dp[i]);
		i--;
	}
	free(utils->dp);
}