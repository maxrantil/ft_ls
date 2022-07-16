/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_recurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/16 07:00:27 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void flag_recurse(char *name, int indent)
{
    struct dirent *dirp;
    DIR *dp;
	char path[1024];

    if (!(dp = opendir(name)))
        return ;
    while ((dirp = readdir(dp)) != NULL)
	{
        if (dirp->d_type == DT_DIR)
		{
            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, dirp->d_name);
            printf("%*s[%s]\n", indent, "", dirp->d_name);
            flag_recurse(path, indent + 2);
        }
		else
		{
            printf("%*s- %s\n", indent, "", dirp->d_name);
        }
    }
    closedir(dp);
}

//	unsigned short d_reclen;    length of this record
//  unsigned char  d_type;      type of file; not supported by all file system types