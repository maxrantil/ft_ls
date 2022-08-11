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
	int				i;
	int				j;
	char			str_flags[MAX_FLAGS];
	unsigned int	bit_flags[MAX_FLAGS];
 
	i = 0;
	int k = 0;
	int l = 0;
	j = 0;
	int check = 0;
	ft_memset(bit_flags, 0, MAX_FLAGS * sizeof(bit_flags[0]));
	ft_bzero(str_flags, MAX_FLAGS);
	printf("%s\n", str_flags);
	if (argc == 1)
		noflag(dirp, ".");
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			p = (char *)(argv[1] + 1);
			int n = ft_strlen(p);
			while (LS_FLAGS[k])
			{
				if (LS_FLAGS[k] == *p && bit_flags[j] == 0 && j != MAX_FLAGS - 1)
				{
					//printf("WORLD ");
					while (i < n)
					{
						j = 0;
						while (j < n)
						{
							if (p[i] == p[j] && i != j)
							{
								check++;
								if (check > 1)
								{
									check = 0;
									break ;
								}
							}
							j++;
						}
						if (j == n)
						{
							bit_flags[j] ^= 1 << i;
							str_flags[l++] = p[i];
						}
						i++;
					}
					/* {
						bit_flags[j] ^= 1 << i;
						str_flags[j++] = *p++;
						i = 0;
						continue ;	
					} */
				}
				k++;
				/* if (*p == 'a')
					noflag(dirp, ".");
				else if (*p == 'l')
					flag_l(dirp, ".");
				else if (*p == 'R')
					flag_recurse(dirp, ".");
				else
					usage(1); */
				//p++;	
			}
		}
		else
			noflag(dirp, argv[1]);
	}
	else
		usage(1);
	printf("%s\n", str_flags);
	return (0);
}
