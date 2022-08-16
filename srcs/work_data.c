#include "ft_ls.h"

static void	turn_on_flag_bits(t_ls *utils)
{
	int	i;

	i = 0;
	while (utils->flags[i])
	{
		if (utils->flags[i] == 'a')
			utils->bit_flags |= 1;
		if (utils->flags[i] == 'l')
			utils->bit_flags |= 2;
		if (utils->flags[i] == 'r')
			utils->bit_flags |= 4;
		if (utils->flags[i] == 'R')
			utils->bit_flags |= 8;
		if (utils->flags[i] == 't')
			utils->bit_flags |= 16;
		i++;
	}
}

static void	exec_flags(t_ls *utils)
{
	if (utils->bit_flags == NULL_FLAG)
		noflag(utils->dirp, ".");
	else
		ft_printf("%b\n", utils->bit_flags);
}

void	work_data(t_ls *utils)
{
	turn_on_flag_bits(utils);
	exec_flags(utils);
	ft_strdel(&utils->flags);
	vec_iter(&utils->v_paths, print_str);
	vec_free(&utils->v_paths);
}