/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_capital_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:46:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/11 21:02:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void flag_capital_r(char *base_path, const int root)
{
    int		i;
    char	path[1000];
	struct	dirent *dirp;
	DIR		*dir;

    dir = opendir(base_path);
	if (!dir)
        return;
    while ((dirp = readdir(dir)) != NULL)
    {
        if (ft_strcmp(dirp->d_name, ".") != 0 && ft_strcmp(dirp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++) 
            {
                if (i%2 == 0 || i == 0)
                    ft_printf("|");
                else
                    ft_printf(" ");
            }
            ft_printf("|-%s\n", dirp->d_name);
            ft_strcpy(path, base_path);
            ft_strcat(path, "/");
            ft_strcat(path, dirp->d_name);
            flag_capital_r(path, root + 2);
        }
    }
    closedir(dir);
}