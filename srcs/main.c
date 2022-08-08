/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/17 12:54:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	usage(int status)
{
	ft_printf("Usage: %s [OPTION]... [FILE]...\n", "./ft_ls");
	ft_printf("\
	List information about the FILEs (the current directory by default).\n\
	Sort entries alphabetically if not -t is specified.\n");
	ft_printf("\
	-a	do not ignore entries starting with .\n\
	-l	use a long listing format\n\
	-r	reverse order while sorting\n\
	-R	list subdirectories recursively\n\
	-t	sort by modification time, newest first\n");
	exit(status);
}

int main(int argc, const char **argv)
{
	struct	dirent	*dirp;
	char			*p;

	if (argc == 1)
		noflag(dirp, ".");
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			p = (char *)(argv[1] + 1);
			while (*p)
			{
				if (*p == 'a')
					noflag(dirp, ".");
				else if (*p == 'l')
					flag_l(dirp);
				else if (*p == 'R')
					flag_recurse(dirp, ".");
				else
					usage(1);
				p++;	
			}
		}
		else
			noflag(dirp, argv[1]);
	}
	else
		usage(1);
	//free(dirp);
	return (0);
}
