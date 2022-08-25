/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:36 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/25 16:57:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (is_bit_set(utils->bit_flags, CAPITAL_R))
		flag_recurse(utils);
	else if (is_bit_set(utils->bit_flags, L_FLAG))
		flag_l(utils);
	else
		flag_null(utils);
}

static void	free_dirs(t_ls *utils)
{
	ssize_t	i;

	if (utils->v_paths.len)
		i = utils->v_paths.len - 1;
	else
		i = 0;
	while (i >= 0)
	{
		if (closedir(utils->dp[i]) < 0)
			exit(1);
		i--;
	}
	free(utils->dp);
}

void	work_data(t_ls *utils, char *flags)
{
	turn_on_bit_flags(utils, flags);
	malloc_directory_ptr(utils);
	exec_flags(utils);
	free_dirs(utils);
}
