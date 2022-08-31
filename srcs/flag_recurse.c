/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/31 19:39:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exec_flag_recurse(t_ls *utils, t_vec *v_rec_path, size_t i)
{
	char	path[MAX_PATH];
	t_data	data;
	t_vec	v_files;
	DIR		*dp;

	if (is_bit_set(utils->bit_flags, L_FLAG))
		init_data(&data);
	ft_strcpy(path, (const char *)vec_get(v_rec_path, i));
	dp = opendir(path);
	ft_printf("%s:\n", path);
	vec_new(&v_files, 0, MAX_FILENAME);
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (check_flag_a(utils))
			continue ;
		pathcat(path, utils->dirp->d_name, "");
		if (is_bit_set(utils->bit_flags, L_FLAG))
		{
			lstat(path, &utils->statbuf);
			get_data(utils->statbuf, &data);
		}
		vec_push(&v_files, path);
	}
	print_it(utils, v_files, &data, i);
	if (i != v_rec_path->len - 1)
		ft_putchar('\n');
	vec_free(&v_files);
	closedir(dp);
}

void	get_dirs_recurse(t_ls *utils, t_vec *v_rec_path,
	char *base_path, size_t i)
{
	char	path[MAX_PATH];
	DIR		*dp;
	
	if (!(dp = opendir(base_path)))
		return ;
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (check_flag_a(utils))
			continue ;
		pathcat(path, utils->dirp->d_name, base_path);
		lstat(path, &utils->statbuf);
		if (S_ISDIR(utils->statbuf.st_mode))
			vec_push(v_rec_path, path);
		exec_flag_recurse(utils, *v_rec_path, i);	
		//get_dirs_recurse(utils, v_rec_path, path, i);
	}
	//sort_it(v_rec_path, utils->bit_flags);
	//ft_printf("i%i", i);
	closedir(dp);
}

void	flag_recurse(t_ls *utils)
{
	t_vec	v_rec_path;
	size_t	i;

	i = 0;
	vec_new(&v_rec_path, 0, MAX_PATH);
	while (i < utils->v_input_paths.len)
	{
		vec_push(&v_rec_path, (char *)vec_get(&utils->v_input_paths, i));
		exec_flag_recurse(utils, &v_rec_path, i);
		get_dirs_recurse(utils, &v_rec_path, \
			(char *)vec_get(&utils->v_input_paths, i), i);
		i++;
	}
	vec_free(&v_rec_path);
}
