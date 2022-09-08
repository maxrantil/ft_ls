/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/08 14:23:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	look_for_dirs(t_ls *utils, t_vec *v_files)
{
	char	input_path[MAX_FILENAME];
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
	//char	*file;
	t_data	data;
	t_vec	v_files;
	DIR		*dp;

	vec_new(&v_files, 0, MAX_FILENAME);
	if (is_bit_set(utils->bit_flags, L_FLAG))
		init_data(&data);
	print_newline_and_path(utils, input_path, i);
	dp = opendir(input_path);
	if (!dp)
	{
		perror("");
		ft_putchar('\n');
		return ;
	}
	while ((utils->dirp = readdir(dp)))
	{
		if (check_flag_a(utils, utils->dirp))
			continue ;
		ft_bzero(path, ft_strlen(path));
		//file = put_path_infront_of_file(utils, i);
		pathcat(path, utils->dirp->d_name, input_path);
		if (is_bit_set(utils->bit_flags, L_FLAG))
		{
			lstat(path, &utils->statbuf);
			get_data(utils->statbuf, &data);
		}
		vec_push(&v_files, path);
	}
	sort_and_print_it(utils, v_files, &data, i);
	closedir(dp);
	look_for_dirs(utils, &v_files);
	vec_free(&v_files);
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
