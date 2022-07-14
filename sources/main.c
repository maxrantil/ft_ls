/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/14 13:40:18 by mrantil          ###   ########.fr       */
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
	closedir(dir);
}

int cmpfunc_str(void *a, void *b)
{
	//return (ft_tolower(*(char *)a) - ft_tolower(*(char *)b)); 
	if (ft_strcmp((char *)a, (char *)b))
		return (*(char *)a);
	else
		return (*(char *)b);
}

void print_str(void *src)
{
	ft_printf("%-*s ", ft_strlen((char *)src) + 1, (char *)src);
}

void	noflag(struct dirent *dirp)
{
	t_vec	noflag;
	DIR		*dir;
	int		ret;
	
	dir = open_path(".");
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
	{
		noflag(dirp);
	}
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
		{
			lst_noflag(dirp);
		}
	}
	else if (argc == 3)
	{
		lst_noflag(dirp);
	}
	else if (argc == 4)
	{
		int ret;
		ret = ft_qsort(argv);
		return (ret);
	}
	else
	{
		perror("usage: ./ft_ls [-laRt] [FILE]...\n");
	}
	return (0);
}
