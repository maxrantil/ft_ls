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

static void get_dirs_recurse(t_vec *vec, struct dirent	*dirp, char *base_path)
{
	char 	path[1024];
    DIR		*dp;

    if (!(dp = opendir(base_path)))
        return ;
    while ((dirp = readdir(dp)) != NULL)
	{
        if (dirp->d_type == DT_DIR)
		{
            if (ft_strcmp(dirp->d_name, ".") == 0 || ft_strcmp(dirp->d_name, "..") == 0 || dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
				continue;
			ft_strcpy(path, base_path);
            ft_strcat(path, "/");
            ft_strcat(path, dirp->d_name);
			vec_push(vec, &path);
            get_dirs_recurse(vec, dirp, path);
        }
    }
	if (closedir(dp) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}

//  unsigned char  d_type;      type of file; not supported by all file system types
void print_files(void *src)
{
	struct dirent	*dirp;
	DIR				*dp;
	t_vec			v_files;
	size_t			file_count;

	file_count = count_files((char *)src);
	vec_new(&v_files, 1, 256 * file_count);
	dp = open_path((const char *)src);
	printf("%s:\n", (char *)src);
	char *joini = ft_strjoin((char *)src, "/");
    while ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strcmp(dirp->d_name, ".") == 0 || ft_strcmp(dirp->d_name, "..") == 0 || dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
			continue; 
		char *print = ft_strjoin(joini, dirp->d_name);
 		//vec_push(&v_files, dirp->d_name);
		vec_push(&v_files, print);
		free(print);
    }
	free(joini);
	vec_sort(&v_files, cmpfunc_str);
	//vec_iter(&v_files, print_str);
	vec_iter(&v_files, print_stat);
	vec_free(&v_files);
	free(dirp);
	free(dp);
	printf("\n\n");
}

void flag_recurse(struct dirent	*dirp, char *base_path)
{
	t_vec			vec;

	vec_new(&vec, 1, sizeof(t_vec));
	vec_push(&vec, base_path);
	get_dirs_recurse(&vec, dirp, base_path);
	vec_sort(&vec, &cmpfunc_str);
	vec_iter(&vec, print_files);
	vec_free(&vec);
}