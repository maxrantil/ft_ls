/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:49:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/31 12:06:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exec_flag_l(t_ls *utils, size_t i)
{
	t_data	data;
	t_vec	v_files;
	DIR		*dp;
	char	path[MAX_PATH];
	char	*file;

	vec_new(&v_files, 0, MAX_FILENAME);
	init_data(&data);																//use memset 0 here?
	ft_strcpy(path, (const char *)vec_get(&utils->v_input_paths, i));
	dp = opendir(path);
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (!is_bit_set(utils->bit_flags, A_FLAG) \
			&& utils->dirp->d_name[0] == '.')
			continue ;
		file = put_path_infront_of_file(utils, i);
		lstat(file, &utils->statbuf);
		get_data(utils->statbuf, &data);
		vec_push(&v_files, file);
		if (utils->v_input_paths.len)
			ft_strdel(&file);
	}
	print_it(utils, v_files, &data, i);
	vec_free(&v_files);
	free(dp);
}

void	flag_l(t_ls *utils)
{
	size_t	i;

	i = 0;
	while (i < utils->v_input_paths.len)
	{
		exec_flag_l(utils, i);
		i++;
	}
}
