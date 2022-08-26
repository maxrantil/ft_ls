/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:26:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	usage(int status)
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

//too long function
static char	*get_flags(char *str)
{
	static int	int_flags[MAX_FLAGS];
	char		*ret_str;
	int			i;
	int			j;
	int			k;
	int			n;

	ret_str = ft_strnew(MAX_FLAGS);
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

static char	*get_data(t_ls *utils, const char **argv, int argc)
{
	char	*ptr;
	char	*temp;
	char	*flags;
	int		i;

	flags = ft_strnew(MAX_FLAGS);
	i = 0;
	while (++i < argc)
	{
		ptr = (char *)argv[i];
		lstat(ptr, &utils->statbuf);
		if (argv[i][0] == '-' && ft_isalpha(argv[i][1]))
		{
			ptr++;
			temp = get_flags(ptr);
			ft_strcat(flags, temp);
			free(temp);
		}
		else
			vec_push(&utils->v_paths, ptr);
		//else if (S_ISDIR(utils->statbuf.st_mode))
		//	ft_printf("%-*s", 2, ptr);
	}
	return (flags);
}

int	main(int argc, const char **argv)
{
	t_ls			utils;
	char			*flags;

	vec_new(&utils.v_paths, 0, MAX_PATH);
	flags = get_data(&utils, argv, argc);
	work_data(&utils, flags);
	vec_free(&utils.v_paths);
	return (0);
}
