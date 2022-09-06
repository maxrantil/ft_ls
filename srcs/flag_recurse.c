/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/06 12:37:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	look_for_dirs(t_ls *utils, t_vec *v_files)
{
	char	input_path[MAX_PATH];
	size_t	i;

	i = 0;
	while (i < v_files->len)
	{
		ft_strcpy(input_path, vec_get(v_files, i));
		lstat(input_path, &utils->statbuf);
		if (S_ISDIR(utils->statbuf.st_mode))
			exec_flag_recurse(utils, input_path, i);
		i++;
	}
}

void	exec_flag_recurse(t_ls *utils, char *input_path, size_t i)
{
	char	path[MAX_PATH];
	t_data	data;
	t_vec	v_files;
	DIR		*dp;

	vec_new(&v_files, 0, MAX_FILENAME);
	if (is_bit_set(utils->bit_flags, L_FLAG))
		init_data(&data);
	dp = opendir(input_path);
	ft_printf("%s:\n", input_path);
	while ((utils->dirp = readdir(dp)))
	{
		if (check_flag_a(utils))
			continue ;
		pathcat(path, utils->dirp->d_name, input_path);
		lstat(path, &utils->statbuf);
		if (is_bit_set(utils->bit_flags, L_FLAG))
			get_data(utils->statbuf, &data);
		vec_push(&v_files, path);
	}
	print_it(utils, v_files, &data, i);
	look_for_dirs(utils, &v_files);
	vec_free(&v_files);
	closedir(dp);
}

void	flag_recurse(t_ls *utils)
{
	size_t	i;

	i = 0;
	while (i < utils->v_input_paths.len)
	{
		exec_flag_recurse(utils, (char *)vec_get(&utils->v_input_paths, i), i);
		i++;
	}
}
