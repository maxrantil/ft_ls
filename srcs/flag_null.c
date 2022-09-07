/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:43:51 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/07 20:10:16 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	exec_flag_null(t_ls *utils, size_t i)
{
	t_vec	v_files;
	DIR		*dp;
	char	path[MAX_PATH];
	char	*file;

	vec_new(&v_files, 0, MAX_FILENAME);
	ft_strcpy(path, (const char *)vec_get(&utils->v_input_paths, i));
	dp = opendir(path);
	if (utils->v_input_paths.len > 1)// && !utils->v_input_files.len)
		ft_printf("%s:\n", path);
	if (!dp)
	{
		print_error(path);
		return ;
	}
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (!is_bit_set(utils->bit_flags, A_FLAG) \
			&& utils->dirp->d_name[0] == '.')
			continue ;
		file = put_path_infront_of_file(utils, i);
		vec_push(&v_files, file);
		if (utils->v_input_paths.len)
			ft_strdel(&file);
	}
	sort_it(&v_files, utils->bit_flags);
	print_files(&v_files, i);
	free(dp);
	vec_free(&v_files);
}

void	flag_null(t_ls *utils)
{
	size_t	i;

	i = 0;
	while (i < utils->v_input_paths.len)
	{
		exec_flag_null(utils, i);
		i++;
	}
}
