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

    if (!(utils->dp[i] = opendir(base_path)))
        return ;
    while ((utils->dirp = readdir(utils->dp[i])) != NULL)
	{
        if (utils->dirp->d_type == DT_DIR)
		{
            if (ft_strcmp(utils->dirp->d_name, ".") == 0 || ft_strcmp(utils->dirp->d_name, "..") == 0 || utils->dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
				continue;
			ft_strcpy(path, base_path);
			ft_strcat(path, "/");
            ft_strcat(path, utils->dirp->d_name);
			vec_push(vec, &path);
            get_dirs_recurse(utils, vec, path, i++);
        }
    }
	if (closedir(utils->dp[i]) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}

static void flag_recurse(t_ls *utils, size_t i)
{
	t_vec	v_files;
	char	*file;
	size_t	file_count;
 
	//dp = open_path_rec((const char *)src);
	file = (char *)vec_get(&utils->v_paths, i);
	file_count = count_files(utils, i);
	vec_new(&v_files, 1, MAX_FILENAME * file_count);
	printf("%s:\n", file);
    while ((utils->dirp = readdir(utils->dp[i])) != NULL)
	{
		if (ft_strcmp(utils->dirp->d_name, ".") == 0 || ft_strcmp(utils->dirp->d_name, "..") == 0 || utils->dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
			continue;
 		vec_push(&v_files, utils->dirp->d_name);
    }
	vec_sort(&v_files, cmpfunc_str);
	//vec_iter(&v_files, print_str);
	print_files(utils, &v_files, i);
	vec_free(&v_files);
	printf("\n\n");
}

/* static void print_files_with_stat(void *src)
{
	struct dirent	*dirp;
	DIR				*dp;
	t_vec			v_files;
	size_t			file_count;

	file_count = count_files((char *)src);
	vec_new(&v_files, 1, 256 * file_count);
	dp = open_path((const char *)src);
	printf("%s:\n", (char *)src);
	ft_strcat((char *)src, "/");
    while ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strcmp(dirp->d_name, ".") == 0 || ft_strcmp(dirp->d_name, "..") == 0 || dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
			continue; 
		char *print = ft_strjoin((char *)src, dirp->d_name);
		vec_push(&v_files, print);
		free(print);
    }
	vec_sort(&v_files, cmpfunc_str);
	vec_iter(&v_files, print_stat);
	vec_free(&v_files);
	free(dirp);
	free(dp);
	printf("\n\n");
} */

void exec_flag_recurse(t_ls *utils, char *base_path)
{
	t_vec	vec;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	vec_new(&vec, 1, sizeof(t_vec));
	vec_push(&vec, base_path);
	//vec_iter(&vec, flag_recurse);
	while (i < vec.len)
	{
		while (j < vec.len)
		{
			utils->dp[j] = open_path(utils, j);
			j++;
		}
		if (utils->dp[i])
		{
			get_dirs_recurse(utils, &vec, base_path, i);
			vec_sort(&vec, &cmpfunc_str);
			flag_recurse(utils, i);
		}
	}
	vec_free(&vec);
}