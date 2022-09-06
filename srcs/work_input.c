/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:36 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/06 12:58:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	turn_on_bit_flags(t_ls *utils, char *flags)
{
	int	i;

	utils->bit_flags = 0b00000;
	i = 0;
	while (flags[i])
	{
		if (flags[i] == 'a')
			utils->bit_flags |= 0b00001;
		if (flags[i] == 'l')
			utils->bit_flags |= 0b00010;
		if (flags[i] == 'r')
			utils->bit_flags |= 0b00100;
		if (flags[i] == 'R')
			utils->bit_flags |= 0b01000;
		if (flags[i] == 't')
			utils->bit_flags |= 0b10000;
		i++;
	}
	ft_strdel(&flags);
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

static void	no_input(t_ls *utils)
{
	size_t	i;
	
	i = 0;
	vec_push(&utils->v_input_paths, ".");			//can we put this in the start of function?
	if (is_bit_set(utils->bit_flags, CAPITAL_R))
		exec_flag_recurse(utils, ".", i);
	else if (is_bit_set(utils->bit_flags, L_FLAG))
		exec_flag_l(utils, i);
	else
		flag_null(utils);
}

void	work_input(t_ls *utils, char *flags)
{
	turn_on_bit_flags(utils, flags);
	if (utils->v_input_files.len)
		print_it(utils, utils->v_input_files, 0, 0);
	if (!utils->v_input_files.len && !utils->v_input_paths.len && !utils->v_input_errors.len)
		no_input(utils);
	else if (utils->v_input_paths.len)
	{
		sort_it(&utils->v_input_paths, utils->bit_flags);
		exec_flags(utils);
	}
	vec_free(&utils->v_input_paths); 		//is this the right place?
	vec_free(&utils->v_input_files);
}
