/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/01 15:09:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"

void	ft_ls(struct dirent *d, DIR *dir)
{
	while ((d = readdir(dir)) != NULL)
	{
		if (d->d_name[0] == '.')
			continue;
		ft_printf("%s ", d->d_name);
	}
	ft_printf("\n");
}

int main(int argc, const char **argv)
{
	struct dirent *d;
	DIR *dir;

	dir = opendir(".");
	if (!dir)
	{
		perror("error, cant read the directory");
		exit(EXIT_FAILURE);
	}
	if (argc > 1)
	{
		if (argv[1][0] == '-')
		{
			if (argv[1][1] == 'a')
			{
				while ((d = readdir(dir)) != NULL)
				{
					if (d->d_name[0] == '.')
						continue;
					ft_printf("%s\n", d->d_name);
				}
				ft_printf("\n");
			}
			if (argv[1][1] == 'l')
			{
				while ((d = readdir(dir)) != NULL)
				{
					ft_printf("%s\n", d->d_name);
				}
				ft_printf("\n");
			}
		}
	}
	else
	{
		while ((d = readdir(dir)) != NULL)
		{
			if (d->d_name[0] == '.')
				continue;
			ft_printf("%*s ", 20, d->d_name);
		}
		ft_printf("\n");
	}
	closedir(dir);
	return (0);
}
