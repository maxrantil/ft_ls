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

static char	*get_flags(char *str)
{
	static int	int_flags[MAX_FLAGS]; //static for if there is many argv starting with dash
	char		*ret_str;
	int			i;
	int			j;
	int			k;
	int			n;
	
	ret_str = (char *)ft_strnew(MAX_FLAGS);
	n = ft_strlen(str);
	i = 0;
	k = 0;
	while (i < n)
	{
		j = 0;
		while (j <= MAX_FLAGS)
		{
			if (LS_FLAGS[j] == str[i])
				break ;
			if (j == MAX_FLAGS)
				usage(1);
			j++;
		}
		if (!int_flags[j])
		{
			int_flags[j] = 1;
			ret_str[k++] = str[i];
		}
		i++;
	}
	return (ret_str);
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
			p = get_flags(p);
				/* if (*p == 'a')
					noflag(dirp, ".");
				else if (*p == 'l')
					flag_l(dirp, ".");
				else if (*p == 'R')
					flag_recurse(dirp, ".");
				else
					usage(1); */
				//p++;	
				printf("%s\n", p);
				free(p);
		}
		else
			noflag(dirp, argv[1]);
	}
	else
		usage(1);
	return (0);
}
