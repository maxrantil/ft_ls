/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/08 13:58:19 by mrantil          ###   ########.fr       */
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

void	print_permissions(struct stat statbuf)
{
	ft_printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    ft_printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");	
}

void	print_file_props(struct stat statbuf)
{
	char	mtime[16];
	
    print_permissions(statbuf);
    ft_strcpy(mtime, ctime(&statbuf.st_mtime));
	ft_printf(" %.12s ", &(mtime[ft_strlen(mtime) - 21]));
}

void	lst_lflag(struct dirent *dp, DIR *dir)
{
	struct	stat statbuf;
	
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] == '.')
			continue;
		if (!stat(dp->d_name, &statbuf))
		{
			print_file_props(statbuf);
			ft_printf("%s\n", dp->d_name);
		}
		else
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}	
	}
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
				lst_lflag(dp, dir);
		}
		else
		{
			dir = open_path(dir, argv[1]);
			lst_noflag(dp, dir);
		}
	}
	else
	{
		dir = open_path(dir, argv[2]);
		lst_noflag(dp, dir);
	}
	closedir(dir);
	return (0);
}
