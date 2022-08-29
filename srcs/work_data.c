/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:36 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/29 12:34:13 by mrantil          ###   ########.fr       */
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

/* static void	malloc_directory_ptr(t_ls *utils)
{
	if (!utils->v_input_paths.len)
	{
		utils->dp = (DIR **)malloc(sizeof(DIR *) * 1);
		utils->dp[0] = opendir(".");
	}
	else
		utils->dp = (DIR **)malloc(sizeof(DIR *) * utils->v_input_paths.len);
} */

static void	exec_flags(t_ls *utils)
{
	if (is_bit_set(utils->bit_flags, CAPITAL_R))
		flag_recurse(utils);
	else if (is_bit_set(utils->bit_flags, L_FLAG))
		flag_l(utils);
	else
		flag_null(utils);
}

/* static void	free_dirs(t_ls *utils)
{
	ssize_t	i;

	if (utils->v_input_paths.len)
		i = utils->v_input_paths.len - 1;
	else
		i = 0;
	while (i >= 0)
	{
		if (closedir(utils->dp[i]) < 0)
			exit(1);
		i--;
	}
	free(utils->dp);
} */

static void	no_input(t_ls *utils)
{
	t_vec	v_no_input;
	size_t	i;
	
	i = 0;
	vec_new(&v_no_input, 0, MAX_PATH);
	if (is_bit_set(utils->bit_flags, CAPITAL_R))
	{
		vec_push(&v_no_input, ".");
		get_dirs_recurse(utils, &v_no_input, ".", i);
		sort_it(&v_no_input, utils->bit_flags);
		while (i < v_no_input.len)
		{
			exec_flag_recurse(utils, v_no_input, i);
			i++;
		}
	}
	else if (is_bit_set(utils->bit_flags, L_FLAG))
	{
		vec_push(&utils->v_input_paths, ".");			//can we put this in the start of function?
		exec_flag_l(utils, i);
	}
	else
	{
		vec_push(&utils->v_input_paths, ".");
		flag_null(utils);
	}
	vec_free(&v_no_input);
}

void	work_data(t_ls *utils, char *flags)
{
	turn_on_bit_flags(utils, flags);
	if (utils->v_input_files.len)
	{
		sort_it(&utils->v_input_files, utils->bit_flags);
		print_it(utils, utils->v_input_files, 0, 0);
	}
	//malloc_directory_ptr(utils);
	if (!utils->v_input_paths.len && !utils->input_errors) 				//files.len will allways be 0 here?
		no_input(utils);
	else if (utils->v_input_paths.len)
	{
		sort_it(&utils->v_input_paths, utils->bit_flags);
		exec_flags(utils);
	}
	vec_free(&utils->v_input_paths); 		//is this the right place?
	vec_free(&utils->v_input_files);
	/* free_dirs(utils); */
}
