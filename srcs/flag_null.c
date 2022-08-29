/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:43:51 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/29 13:46:17 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	exec_flag_null(t_ls *utils, size_t i)
{
	t_vec	v_files;
	DIR		*dp;
	char	path[MAX_PATH];

	vec_new(&v_files, 0, MAX_FILENAME);
	ft_strcpy(path, (const char *)vec_get(&utils->v_input_paths, i));
	dp = opendir(path);
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (!is_bit_set(utils->bit_flags, A_FLAG) \
			&& utils->dirp->d_name[0] == '.')
			continue ;
		pathcat(path, utils->dirp->d_name, NULL);
		vec_push(&v_files, path);
	}
	//sort_it(&v_files, utils->bit_flags); 				//al thses inside at the top of the print function
	print_it(utils, v_files, i, 0);
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
