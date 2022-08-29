/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/29 20:13:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_dirs_recurse(t_ls *utils, t_vec *v_rec_path,
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
		pathcat(path, utils->dirp->d_name, base_path);
		lstat(path, &utils->statbuf);
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
void	exec_flag_recurse(t_ls *utils, t_vec v_rec_path, size_t i)
{
	t_vec	v_files;
	DIR		*dp;
	char	path[MAX_PATH];
	int		total;

	total = 0;
	ft_strcpy(path, (const char *)vec_get(&v_rec_path, i));
	dp = opendir(path);
	ft_printf("%s:\n", path);									//need to fix if path from input ends with slash, or not! check iMac
	vec_new(&v_files, 0, MAX_FILENAME);
	while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (!is_bit_set(utils->bit_flags, A_FLAG) \
			&& (!ft_strcmp(utils->dirp->d_name, ".") \
				|| !ft_strcmp(utils->dirp->d_name, "..") \
				|| utils->dirp->d_name[0] == '.'))
			continue ;
		pathcat(path, utils->dirp->d_name, "");
		lstat(path, &utils->statbuf);
		total += utils->statbuf.st_blocks;
		vec_push(&v_files, path);
	}
	sort_it(&v_files, utils->bit_flags);
	print_it(utils, v_files, i, total);
	if (i != v_rec_path.len - 1)
		ft_putchar('\n');
	vec_free(&v_files);
	closedir(dp);
}

//too long function
void	flag_recurse(t_ls *utils)
{
	t_vec	v_rec_path;
	size_t	i;
 	size_t	j;

	i = 0;
 	j = 0;
	vec_new(&v_rec_path, 0, MAX_PATH);
	while (i < utils->v_input_paths.len)
	{
		vec_push(&v_rec_path, (char *)vec_get(&utils->v_input_paths, i));
		get_dirs_recurse(utils, &v_rec_path, \
			(char *)vec_get(&utils->v_input_paths, i), i);
		sort_it(&v_rec_path, utils->bit_flags);
		while (j < v_rec_path.len)
		{
			exec_flag_recurse(utils, v_rec_path, j);
			j++;
		}
		i++;
	}
	vec_free(&v_rec_path);
}
