/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/16 19:22:54 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void flag_recurse(char *base_path, int indent)
{
    struct	dirent *dirp;
	t_utils	utils;
	char 	path[1024];
    DIR		*dp;

	utils.dir_count = 0;
	utils.file_count = 0;
    if (!(dp = opendir(base_path)))
        return ;
    while ((dirp = readdir(dp)) != NULL)
	{
        if (dirp->d_type == DT_DIR)
		{
            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 || dirp->d_name[0] == '.') //hidden maps dont show
                continue;
			ft_strcpy(path, base_path);
            ft_strcat(path, "/");
            ft_strcat(path, dirp->d_name);
			utils.dir_count++;
            ft_printf("\n\n%*s%d%s\n", indent, "", indent, path);
            flag_recurse(path, indent + 1);
        }
		else
		{
			utils.file_count++;
            ft_printf("%*s%d%-*s", indent, "", indent, 15, dirp->d_name);
        }
    }
	ft_printf("\n\n{gre}dir_count = %d{nor}\n", utils.dir_count);
	ft_printf("\n\n{blu}file_count = %d{nor}\n", utils.file_count);
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