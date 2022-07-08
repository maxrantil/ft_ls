/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/08 09:15:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	lst_noflag(struct dirent *d, DIR *dir)
{
	while ((d = readdir(dir)) != NULL)
	{
		if (d->d_name[0] == '.')
			continue;
		ft_printf("%-*s ", ft_strlen(d->d_name) + 1, d->d_name);
	}
	ft_printf("\n");
}

void	lst_lflag(struct dirent *d, DIR *dir)
{
	struct	stat *buf;
	
	buf = malloc(sizeof(struct stat));
	while ((d = readdir(dir)) != NULL)
	{
		if (d->d_name[0] == '.')
			continue;
		stat(d->d_name, buf);
		int size = buf->st_size;
		printf("%d",size);
		ft_printf("%s\n ", d->d_name);
	}
	free(buf);
}
	

DIR*	open_path(DIR *dir, const char *str)
{
	dir = opendir(str);
	if (!dir)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (dir);
}

int main(int argc, const char **argv)
{
	struct	dirent *d;
	DIR		*dir;

	if (argc == 1)
	{
		dir = open_path(dir, ".");
		lst_noflag(d, dir);
	}
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			dir = open_path(dir, ".");
			if (argv[1][1] == 'a')
				lst_noflag(d, dir);
			if (argv[1][1] == 'l')
				lst_lflag(d, dir);
		}
		else
		{
			dir = open_path(dir, argv[1]);
			lst_noflag(d, dir);
		}
	}
	else
	{
		dir = open_path(dir, argv[2]);
		lst_noflag(d, dir);
	}
	closedir(dir);
	return (0);
}
