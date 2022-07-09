/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/09 13:00:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	lst_noflag(struct dirent *dp, DIR *dir)
{
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] == '.')
			continue;
		ft_printf("%-*s", ft_strlen(dp->d_name) + 2, dp->d_name);
	}
	ft_printf("\n");
}

DIR*	open_path(DIR *dir, const char *str)
{
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
	struct	dirent *dp;
	DIR		*dir;

	if (argc == 1)
	{
		dir = open_path(dir, ".");
		lst_noflag(dp, dir);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			dir = open_path(dir, ".");
			if (argv[1][1] == 'a')
				lst_noflag(dp, dir);
			if (argv[1][1] == 'l')
				flag_l(dp, dir);
			if (argv[1][1] == 'R')
				flag_capital_r(dp, dir);
		}
		else
		{
			dir = open_path(dir, argv[1]);
			lst_noflag(dp, dir);
		}
	}
	else if (argc == 3)
	{
		dir = open_path(dir, argv[2]);
		lst_noflag(dp, dir);
	}
	else
	{
		dir = NULL;
		ft_printf("usage: ./ft_ls [-laRt] [FILE]...\n");
	}
	closedir(dir);
	return (0);
}
