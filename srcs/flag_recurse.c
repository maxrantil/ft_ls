/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/13 08:43:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_for_dirs(t_ls *utils, t_vec *v_files, ssize_t i)
{
	struct stat	statbuf;
	char		file[MAX_PATH];
	char		nopathfile[MAX_FILENAME];

	ft_strcpy(file, vec_get(v_files, i));
	lstat(file, &statbuf);
	ft_strcpy(nopathfile, no_path(file));
	if (S_ISDIR(statbuf.st_mode) \
	&& ft_strcmp(nopathfile, ".") && ft_strcmp(nopathfile, ".."))
		exec_flag_recurse(utils, file, i);
}

static void	check_order(t_ls *utils, t_vec *v_files)
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
		while ((size_t)i < v_files->len)
		{
			check_for_dirs(utils, v_files, i);
			i++;
		}
	}
}

static void	add_files(t_vec *v_files, char *file, char *path, char *input_path)
{
	pathcat(path, file, input_path);
	vec_push(v_files, path);
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
	while (1)
	{
		utils->dirp = readdir(dp);
		if (!utils->dirp)
			break ;
		if (check_flag_a(utils, utils->dirp))
			continue ;
		add_files(&v_files, utils->dirp->d_name, path, input_path);
	}
	sort_and_print_it(utils, &v_files, i);
	check_order(utils, &v_files);
	closedir(dp);
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
