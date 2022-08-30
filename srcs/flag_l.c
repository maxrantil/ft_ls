/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:49:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/30 17:53:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*put_path_infront_of_file(t_ls *utils, size_t i)
{
	char	*file_with_path;

	if (utils->v_input_paths.len)
	{
		file_with_path = ft_strjoin((char *)vec_get(&utils->v_input_paths, i), "/");
		file_with_path = ft_strupdate(file_with_path, utils->dirp->d_name);
		return (file_with_path);
	}
	return (utils->dirp->d_name);
}

void	exec_flag_l(t_ls *utils, size_t i)
{
	t_data	data;
	t_vec	v_files;
	DIR		*dp;
	char	path[MAX_PATH];
	char	*file;
	//int		total;

	/* data.links_len = 1; */
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
		//data->total += utils->statbuf.st_blocks;		//i can make a struct that will take all data for a good padding here. look belove, but make it in a function of its own that can be called from -R aswell
		/* if (ft_strlen(ft_itoa(utils->statbuf.st_nlink)) > data.links_len)
			utils->v_input_paths.len = ft_strlen(ft_itoa(utils->statbuf.st_nlink); */
		vec_push(&v_files, file);
		if (utils->v_input_paths.len)
			ft_strdel(&file);
	}
	//sort_it(&v_files, utils->bit_flags);
	//print_stat(utils, &v_files, i, total);
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
