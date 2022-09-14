/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:36 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/14 17:33:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	convert_to_bit_flag(t_ls *utils, char *flags)
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
	if (!utils->v_input_files.len && !utils->v_input_paths.len && \
	!utils->v_input_errors.len)
		vec_push(&utils->v_input_paths, ".");
	sort_it(&utils->v_input_paths, utils->bit_flags);
	if (is_bit_set(utils->bit_flags, CAPITAL_R))
		flag_recurse(utils);
	else
		get_files_from_path(utils);
}

void	work_input(t_ls *utils, char *flags)
{
	convert_to_bit_flag(utils, flags);
	if (utils->v_input_files.len)
		sort_and_print_it(utils, &utils->v_input_files, 0);
	exec_flags(utils);
	free_vectors(utils);
}
