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

void flag_recurse(t_vec *vec, char *base_path)
{
    struct	dirent *dirp;
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
            //ft_printf("\n\n%s%s\n", path, ":");
            flag_recurse(vec, path);
        }
		/* else
		{
            ft_printf("%*s%d%-*s", indent, "", indent, 15, dirp->d_name);
        } */
    }
	/* utils.dir = (t_dir *)malloc(sizeof(t_dir) * utils.dir_count);
	if (!utils.dir)
	{
		perror("utils.dir");
		exit(1);
	} */
    closedir(dp);	//read them all into a vec and then print them out into structure after
}

//	unsigned short d_reclen;    length of this record
//  unsigned char  d_type;      type of file; not supported by all file system types