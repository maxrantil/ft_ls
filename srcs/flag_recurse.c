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
		/* else
		{
            ft_printf("%*s%d%-*s", indent, "", indent, 15, dirp->d_name);
        } */
    }
	if (closedir(dp) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}

//	unsigned short d_reclen;    length of this record
//  unsigned char  d_type;      type of file; not supported by all file system types


void flag_recurse(struct dirent	*dirp, char *base_path)
{
	t_vec			vec;

	vec_new(&vec, 1, sizeof(t_vec));
	vec_push(&vec, base_path);
	get_dirs_recurse(&vec, dirp, base_path);
	vec_sort(&vec, &cmpfunc_str);
	vec_iter(&vec, print_str);
	vec_free(&vec);
}