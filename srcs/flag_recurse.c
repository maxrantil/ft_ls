/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/02 10:46:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_bit_set(unsigned int value, unsigned int bitindex)
{
	if (bitindex & (1 << value))
		return (1);
	return (0);
}

static void get_dirs_recurse(t_ls *utils, t_vec *v_rec_path, char *base_path, size_t i)
{
	char 	path[MAX_PATH];
	DIR		*dp;

    if (!(dp = opendir(base_path)))
        return ;
    while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (!ft_strcmp(utils->dirp->d_name, ".") || !ft_strcmp(utils->dirp->d_name, ".."))// || utils->dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
			continue;
		ft_strcpy(path, base_path);
		ft_strcat(path, "/");
		ft_strcat(path, utils->dirp->d_name);
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
	if (closedir(dp) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}

static void exec_flag_recurse(t_ls *utils, t_vec v_rec_path, size_t i)
{
	t_vec	v_files;
	DIR		*dp;
	char	path[MAX_PATH];
	char	*file_with_path;
 
	ft_strcpy(path, (const char *)vec_get(&v_rec_path, i));
    dp = opendir(path);
	if (v_rec_path.len - i - 1 != 0) // fix this later
		ft_printf("%s:\n", path);
	else
		ft_printf("\n%s:\n", path);
	ft_strcat(path, "/");
	vec_new(&v_files, 0, MAX_FILENAME);
    while ((utils->dirp = readdir(dp)) != NULL)
	{
		 if (ft_strcmp(utils->dirp->d_name, ".") == 0 || ft_strcmp(utils->dirp->d_name, "..") == 0)// || utils->dirp->d_name[0] == '.')) //hidden folders dont show(no -a flag)
			continue;
		file_with_path = ft_strjoin(path, utils->dirp->d_name);
		if (vec_push(&v_files, file_with_path) < 0)
		{
			perror("vec_push, exec_flag_recurse");
			exit(1);
		}
		free(file_with_path);
    }
	vec_sort(&v_files, cmpfunc_str);
	print_files(utils, &v_files, i);

	if (v_rec_path.len != 0 && i != v_rec_path.len  - 1) // fix this later
		write(1, "\n\n", 2);
	else
		write(1, "\n", 1);
	
	vec_free(&v_files);
	closedir(dp);
}

void	flag_recurse(t_ls *utils)
{
	t_vec	v_rec_path;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	vec_new(&v_rec_path, 0, MAX_PATH );
	if (!utils->v_paths.len)
	{
		vec_push(&v_rec_path, ".");
		get_dirs_recurse(utils, &v_rec_path, ".", i);
		vec_sort(&v_rec_path, cmpfunc_str);
		while (i < v_rec_path.len)
		{
			exec_flag_recurse(utils, v_rec_path, i);
			i++;
		}
	}
	else
	{
		vec_sort(&utils->v_paths, &cmpfunc_str);
	}
	while (i < utils->v_paths.len) //i think the leak is here somewhere? if v_path.len > 1 then there is a leak.
	{
		vec_push(&v_rec_path, (char *)vec_get(&utils->v_paths, i));
		get_dirs_recurse(utils, &v_rec_path, (char *)vec_get(&utils->v_paths, i), i);
		vec_sort(&v_rec_path, &cmpfunc_str);
		//printf("SER DU?\n");
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

/* void	flag_recurse(t_ls *utils)
{
	t_vec	v_rec_path;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	vec_new(&v_rec_path, 0, MAX_PATH);
	if (!utils->v_paths.len)
	{
		vec_push(&v_rec_path, ".");
		get_dirs_recurse(utils, &v_rec_path, ".", i);
		vec_sort(&v_rec_path, cmpfunc_str);
		while (i < v_rec_path.len)
		{
			exec_flag_recurse(utils, v_rec_path, i);
			i++;
		}
	}
	else
		vec_sort(&utils->v_paths, cmpfunc_str);
	while (i < utils->v_paths.len)
	{
		vec_push(&v_rec_path, (char *)vec_get(&utils->v_paths, i));
		get_dirs_recurse(utils, &v_rec_path, (char *)vec_get(&utils->v_paths, i), i);
		vec_sort(&v_rec_path, cmpfunc_str);
		while (j < v_rec_path.len)
		{
			exec_flag_recurse(utils, v_rec_path, j);
			j++;
		}
		i++;
	}
	vec_free(&v_rec_path);
} */