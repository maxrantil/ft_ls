/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_capital_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/15 13:10:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void flag_capital_r(t_vec *vec, char *base_path)
{
	struct	dirent *dirp;
	//t_dir	ds;
    char	path[10000];
	DIR		*dp;
	int		ret;

    dp = opendir(base_path);
	if (!dp)
        return ;
    while ((dirp = readdir(dp)) != NULL)
    {
        if (ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0 && dirp->d_name[0] != '.')
		{
			ret = vec_push(vec, dirp->d_name);
			if (ret < 0)
			{
				perror("vec_push");
				exit(EXIT_FAILURE);
			}
		}					
		//ft_printf("\n\n%s/%s:\n", base_path, dirp->d_name);
		//	ft_printf("%s\t", dirp->d_name);
		ft_strcpy(path, base_path);
		ft_strcat(path, "/");
		ft_strcat(path, dirp->d_name);
		flag_capital_r(vec, path);
    }
	vec_sort(vec, cmpfunc_str);
	vec_iter(vec, print_str);
	ft_printf("\n");
	vec_free(vec);
    closedir(dp);
}

//	unsigned short d_reclen;    length of this record
//  unsigned char  d_type;      type of file; not supported by all file system types