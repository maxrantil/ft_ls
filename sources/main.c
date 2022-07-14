/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/14 14:47:50 by mrantil          ###   ########.fr       */
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
	DIR		*dir;
	int		ret;
	
	dir = open_path(path);
	vec_new(&noflag, 20, sizeof(dirp->d_name));
	while ((dirp = readdir(dir)) != NULL)
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
	closedir(dir);
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
		noflag(dirp, ".");
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			if (argv[1][1] == 'a')
				lst_noflag(dirp);
			if (argv[1][1] == 'l')
				flag_l(dirp);
			if (argv[1][1] == 'R')
				flag_capital_r(".");
		}
		else
			noflag(dirp, argv[1]);
	}
	else
		perror("usage: ./ft_ls [-laRt] [FILE]...\n");
	return (0);
}
