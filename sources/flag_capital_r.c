/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_capital_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/12 13:32:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void flag_capital_r(char *base_path)
{
	struct	dirent *dirp;
    char	path[1000];
	DIR		*dir;

    dir = opendir(base_path);
	if (!dir)
        return;
    while ((dirp = readdir(dir)) != NULL)
    {
        if (ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0 && dirp->d_name[0] != '.')
        {
			if (dirp->d_type == DT_DIR)
            	ft_printf("\n\n%s/%s:\n", base_path, dirp->d_name);
			else
            	ft_printf("%s\t", dirp->d_name);
            ft_strcpy(path, base_path);
            ft_strcat(path, "/");
            ft_strcat(path, dirp->d_name);
            flag_capital_r(path);
        }
    }
    closedir(dir);
}

//	unsigned short d_reclen;    /* length of this record */
//  unsigned char  d_type;      /* type of file; not supported by all file system types */