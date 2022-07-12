/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/12 12:37:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	lst_noflag(struct dirent *dirp)
{
	DIR		*dir;
	dir = open_path(".");
	
	while ((dirp = readdir(dir)) != NULL)
	{
		if (dirp->d_name[0] == '.')
			continue;
		ft_printf("%-*s", ft_strlen(dirp->d_name) + 2, dirp->d_name);
	}
	ft_printf("\n");
}

DIR*	open_path(const char *str)
{
	DIR *dir;
	
	dir = opendir(str);
	if (!dir)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	return (dir);
}

int main(int argc, const char **argv)
{
	struct	dirent *dirp;

	if (argc == 1)
	{
		lst_noflag(dirp);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			//dir = open_path(dir, ".");
			if (argv[1][1] == 'a')
				lst_noflag(dirp);
			if (argv[1][1] == 'l')
				flag_l(dirp);
			if (argv[1][1] == 'R')
				flag_capital_r(".");
		}
		else
		{
			//dir = open_path(dir, argv[1]);
			lst_noflag(dirp);
		}
	}
	else if (argc == 3)
	{
		//dir = open_path(dir, argv[2]);
		lst_noflag(dirp);
	}
	else
	{
		//dir = NULL;
		perror("usage: ./ft_ls [-laRt] [FILE]...\n");
	}
	//closedir(dir);
	return (0);
}
