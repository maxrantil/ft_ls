/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/15 10:12:00 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int cmpfunc_str(void *a, void *b)
{
	int	ret;
	
	ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	while (*(char *)a && *(char *)b && !ret)
	{
		a++;
		b++;
		ret = ft_tolower(*(char *)a) - ft_tolower(*(char *)b);
	}
	return (ret);
}

void print_str(void *src)
{
	ft_printf("%-*s ", ft_strlen((char *)src) + 1, (char *)src);
}

void	noflag(struct dirent *dirp, const char *path)
{
	t_vec	noflag;
	DIR		*dp;
	int		ret;
	
	dp = open_path(path);
	vec_new(&noflag, 20, sizeof(dirp->d_name));
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] == '.')
			continue ;
		ret = vec_push(&noflag, dirp->d_name);
		if (ret < 0)
		{
			perror("vec_push");
			exit(EXIT_FAILURE);
		}
	}
	vec_sort(&noflag, cmpfunc_str);
	vec_iter(&noflag, print_str);
	ft_printf("\n");
	vec_free(&noflag);
	closedir(dp);
}

DIR*	open_path(const char *str)
{
	DIR *dp;
	
	dp = opendir(str);
	if (!dp)
	{
		perror("open_path");
		exit(EXIT_FAILURE);
	}
	return (dp);
}

void	usage(int status)
{
	if (status != EXIT_SUCCESS)
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
	}
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
			p = (char*)(argv[1] + 1);
			while (*p)
			{
				if (*p == 'a')
					noflag(dirp, ".");
				else if (*p == 'l')
					flag_l(dirp);
				else if (*p == 'R')
					flag_capital_r(".");
				else
					usage(EXIT_FAILURE);
				p++;	
			}
		}
		else
			noflag(dirp, argv[1]);
	}
	else
		perror("usage: ./ft_ls [-laRt] [FILE]...\n");
	return (0);
}
