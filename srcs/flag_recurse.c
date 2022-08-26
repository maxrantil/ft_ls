/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/25 16:08:43 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	pathcat_maker(char *path, char *file_name, char *base_path)
{
	ft_strcpy(path, base_path);
	ft_strcat(path, "/");
	ft_strcat(path, file_name);
}

static void	get_dirs_recurse(t_ls *utils, t_vec *v_rec_path,
	char *base_path, size_t i)
{
	char	path[MAX_PATH];
	DIR		*dp;

	if (!(dp = opendir(base_path)))
		return ;
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (!ft_strcmp(utils->dirp->d_name, ".")
			||!ft_strcmp(utils->dirp->d_name, "..")
			|| (!is_bit_set(utils->bit_flags, A_FLAG)
				&& utils->dirp->d_name[0] == '.'))
			continue ;
		pathcat_maker(path, utils->dirp->d_name, base_path);
		stat(path, &utils->statbuf);
		if (S_ISDIR(utils->statbuf.st_mode))
		{
			if (vec_push(v_rec_path, path) < 0)
			{
				perror("vec_push, get_dir_recurse");
				exit(1);
			}
			get_dirs_recurse(utils, v_rec_path, path, i);
		}
	}
	closedir(dp);
}

//Too long function
static void	exec_flag_recurse(t_ls *utils, t_vec v_rec_path, size_t i)
{
	t_vec	v_files;
	DIR		*dp;
	char	path[MAX_PATH];
	int		total;

	total = 0;
	ft_strcpy(path, (const char *)vec_get(&v_rec_path, i));
	dp = opendir(path);
	ft_printf("%s:\n", path);
	vec_new(&v_files, 0, MAX_FILENAME);
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (!is_bit_set(utils->bit_flags, A_FLAG) \
			&& (!ft_strcmp(utils->dirp->d_name, ".") \
				|| !ft_strcmp(utils->dirp->d_name, "..") \
				|| utils->dirp->d_name[0] == '.'))
			continue ;
		pathcat_maker(path, utils->dirp->d_name, "");
		stat(path, &utils->statbuf);
		total += utils->statbuf.st_blocks;
		vec_push(&v_files, path);
	}
	sort_it(&v_files, utils->bit_flags);
	print_it(utils, v_files, i, total);
	if (i != v_rec_path.len - 1)
		write(1, "\n", 1);
	vec_free(&v_files);
	closedir(dp);
}

//Too long funtion
void	flag_recurse(t_ls *utils)
{
	t_vec	v_rec_path;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	vec_new(&v_rec_path, 0, MAX_PATH);
	if (!utils->v_paths.len)
	{
		vec_push(&v_rec_path, ".");
		get_dirs_recurse(utils, &v_rec_path, ".", i);
		sort_it(&v_rec_path, utils->bit_flags);
		while (i < v_rec_path.len)
		{
			exec_flag_recurse(utils, v_rec_path, i);
			i++;
		}
	}
	else
		sort_it(&utils->v_paths, utils->bit_flags);
	while (i < utils->v_paths.len)
	{
		vec_push(&v_rec_path, (char *)vec_get(&utils->v_paths, i));
		get_dirs_recurse(utils, &v_rec_path, \
			(char *)vec_get(&utils->v_paths, i), i);
		sort_it(&v_rec_path, utils->bit_flags);
		while (j < utils->v_paths.len)
		{
			utils->dp[j] = open_path(utils, j);
			j++;
		}
		if (utils->dp[i])
		{
			while (k < v_rec_path.len)
			{
				exec_flag_recurse(utils, v_rec_path, k);
				k++;
			}
		}
		i++;
	}
	vec_free(&v_rec_path);
}