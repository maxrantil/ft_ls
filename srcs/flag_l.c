/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:49:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/15 09:25:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*put_path_infront_of_file(t_ls *utils, size_t i)
{
	char	*file_with_path;

	if (utils->v_paths.len)
	{
		file_with_path = ft_strjoin((char *)vec_get(&utils->v_paths, i), "/");
		file_with_path = ft_strupdate(file_with_path, utils->dirp->d_name);
		return (file_with_path);
	}
	return (utils->dirp->d_name);
}

static void	exec_flag_l(t_ls *utils, size_t i)
{
	t_vec		v_files;
	char		*file;
	int			total;

	vec_new(&v_files, 0, MAX_FILENAME);
	total = 0;
	while ((utils->dirp = readdir(utils->dp[i])) != NULL)
	{
		if (!is_bit_set(utils->bit_flags, A) && utils->dirp->d_name[0] == '.')
			continue ;
		file = put_path_infront_of_file(utils, i);
		stat(file, &utils->statbuf);
		total += utils->statbuf.st_blocks;
		vec_push(&v_files, file);
		if (utils->v_paths.len)
			ft_strdel(&file);
	}
	sort_it(&v_files, utils->bit_flags);
	print_it(utils, v_files, i, total);
	vec_free(&v_files);
}

void	flag_l(t_ls *utils)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!utils->v_paths.len)
		exec_flag_l(utils, i);
	else
		sort_it(&utils->v_paths, utils->bit_flags);
	while (i < utils->v_paths.len)
	{
		while (j < utils->v_paths.len)
		{
			utils->dp[j] = open_path(utils, j);
			j++;
		}
		if (utils->dp[i])
			exec_flag_l(utils, i);
		i++;
	}
}
