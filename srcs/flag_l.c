/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:49:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/14 11:06:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	push_file(t_ls *utils, t_vec *v_files, size_t i)
{
	char	*file;

	file = put_path_infront_of_file(utils, i);
	vec_push(v_files, file);
	if (utils->v_input_paths.len)
		ft_strdel(&file);
}

void	get_files(t_ls *utils, t_vec *v_files, size_t i)
{
	char	path[MAX_PATH];
	DIR		*dp;

	ft_strcpy(path, (const char *)vec_get(&utils->v_input_paths, i));
	print_newline_and_path(utils, path, i);
	dp = opendir(path);
	if (!dp)
	{
		print_error(path);
		return ;
	}
	while (1)
	{
		utils->dirp = readdir(dp);
		if (!utils->dirp)
			break ;
		if (!is_bit_set(utils->bit_flags, A_FLAG) \
		&& utils->dirp->d_name[0] == '.')
			continue ;
		push_file(utils, v_files, i);
	}
	sort_and_print_it(utils, v_files, i);
	closedir(dp);
}

void	get_files_from_path(t_ls *utils)
{
	t_vec	v_files;
	size_t	i;

	i = 0;
	while (i < utils->v_input_paths.len)
	{
		vec_new(&v_files, 0, MAX_FILENAME);
		get_files(utils, &v_files, i);
		vec_free(&v_files);
		i++;
	}
}
