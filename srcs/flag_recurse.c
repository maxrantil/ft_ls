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

static void get_dirs_recurse(t_ls *utils, t_vec *vec, char *base_path, size_t i)
{
	char 	path[MAX_PATH];
	DIR		*dp;

    if (!(dp = opendir(base_path)))
        return ;
    while ((utils->dirp = readdir(dp)) != NULL)
	{
        if (utils->dirp->d_type == DT_DIR)
		{
            if (ft_strcmp(utils->dirp->d_name, ".") == 0 || ft_strcmp(utils->dirp->d_name, "..") == 0 || utils->dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
				continue;
			ft_strcpy(path, base_path);
			ft_strcat(path, "/");
            ft_strcat(path, utils->dirp->d_name);
			if (vec_push(vec, &path) < 0)
			{
				perror("vec_push, flag_l");
				exit(1);
			}
            get_dirs_recurse(utils, vec, path, i);
        }
    }
	if (closedir(dp) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}

static void exec_flag_recurse(t_ls *utils, t_vec vec, size_t i)
{
	t_vec	v_files;
	DIR		*dp;
	char	*path;
 
	path = (char *)vec_get(&vec, i);
	vec_new(&v_files, 0, MAX_FILENAME);
    dp = opendir(path);
	ft_printf("%s:\n", path);
	path = ft_strupdate(path, "/");
    while ((utils->dirp = readdir(dp)) != NULL)
	{
		if (ft_strcmp(utils->dirp->d_name, ".") == 0 || ft_strcmp(utils->dirp->d_name, "..") == 0 || utils->dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
			continue;
		char *joini = ft_strjoin(path, utils->dirp->d_name);
 		vec_push(&v_files, joini);
		free(joini);
    }
	free(path);
	vec_sort(&v_files, cmpfunc_str);
	print_files(utils, &v_files, i);
	vec_free(&v_files);
	free(dp);
	printf("\n\n");
}

void print_str_vec(void *src)
{
    ft_printf("%-*s", ft_strlen((char *)src) + 2, (char *)src);
}

void	flag_recurse(t_ls *utils)
{
	t_vec	vec;
	size_t	i;
	//size_t	j;

	i = 0;
	//j = 0;
	vec_new(&vec, 0, MAX_PATH);
	//vec_push(&vec, vec_get(&utils->v_paths, i));
	if (!utils->v_paths.len)
		vec_push(&vec, ".");
	else
		vec_push(&vec, (char *)vec_get(&vec, i));
	while (i < vec.len)
	{
	/* 	while (j < vec.len)
		{
			utils->dp[j] = open_path(utils, 9999);
			j++;
		}
	 */	if (utils->dp[i])
		{
			get_dirs_recurse(utils, &vec, ".", i);
			vec_sort(&vec, &cmpfunc_str);
			//vec_iter(&vec, print_str_vec);
			exec_flag_recurse(utils, vec, i);
		}
	}
	vec_free(&vec);
}

/* void	pre_flag_recurse(t_ls *utils)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!utils->v_paths.len)
		flag_recurse(utils);
	else
		vec_sort(&utils->v_paths, cmpfunc_str);
	while (i < utils->v_paths.len)
	{
		while (j < utils->v_paths.len)
		{
			utils->dp[j] = open_path(utils, j);
			j++;
		}
		if (utils->dp[i])
			flag_recurse(utils);
		i++;
	}
} */