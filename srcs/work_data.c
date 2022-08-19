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
}

static void	check_flags(t_ls *utils)
{
	if (utils->bit_flags == NULL_FLAG || (utils->bit_flags ^ A) == 0)
		exec_flag_null(utils);
	else if((utils->bit_flags & L) != 0 || ((utils->bit_flags ^ (L + A)) == 0))
		exec_flag_l(utils);
	else
		ft_printf("%b\n", utils->bit_flags);
}

//utils->bit_flags ^ (L | A | R) == 0

void	work_data(t_ls *utils, char *flags)
{
	turn_on_bit_flags(utils, flags);
	check_flags(utils);

	ft_strdel(&flags);
	vec_free(&utils->v_paths);
	int i = utils->v_paths.len; // lean up this into another function?? or place it right after it is beeing used
	while (i >= 0)
		free(&utils->dp[i--]);
}