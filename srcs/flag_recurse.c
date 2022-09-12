/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 17:49:54 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_for_dirs(t_ls *utils, t_vec *v_files, ssize_t i)
{
	struct stat	statbuf;
	char		input_path[MAX_FILENAME];
	
	ft_strcpy(input_path, vec_get(v_files, i));
	lstat(input_path, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
		exec_flag_recurse(utils, input_path, i);
}

static void	look_for_dirs(t_ls *utils, t_vec *v_files)
{
	ssize_t		i;

	if (is_bit_set(utils->bit_flags, R_FLAG))
	{
		i = v_files->len - 1;
		while (i >= 0)
		{
			check_for_dirs(utils, v_files, i);
			i--;
		}	
	}
	else
	{
		i = 0;
		while (i < (ssize_t)v_files->len)
		{
			check_for_dirs(utils, v_files, i);
			i++;
		}
	}
}

void	exec_flag_recurse(t_ls *utils, char *input_path, size_t i)
{
	char	path[MAX_PATH];
	t_vec	v_files;
	DIR		*dp;

	vec_new(&v_files, 0, MAX_FILENAME);
	print_newline_and_path(utils, input_path, i);
	dp = opendir(input_path);
	if (!dp)
	{
		perror("");
		return ;
	}
	while ((utils->dirp = readdir(dp)))
	{
		if (check_flag_a(utils, utils->dirp))
			continue ;
		ft_bzero(path, ft_strlen(path));
		pathcat(path, utils->dirp->d_name, input_path);
		vec_push(&v_files, path);
	}
	sort_and_print_it(utils, v_files, i); //no path for first if no more then 1 input path
	closedir(dp);
	look_for_dirs(utils, &v_files);
	vec_free(&v_files);
}

void	flag_recurse(t_ls *utils)
{
	ssize_t	i;

	i = 0;
	while (i < (ssize_t)utils->v_input_paths.len)
	{
		exec_flag_recurse(utils, (char *)vec_get(&utils->v_input_paths, i), i);
		i++;
	}	
}
