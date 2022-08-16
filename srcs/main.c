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

uint8_t	turn_on_bits(void *c)
{

	uint8_t	bit_flags;
	
	bit_flags = 0;
	while (*(char *)c)
	{
		if (*(char *)c == 'a')
			bit_flags |= 1;
		if (*(char *)c == 'l')
			bit_flags |= 2;
		if (*(char *)c == 'r')
			bit_flags |= 4;
		if (*(char *)c == 'R')
			bit_flags |= 8;
		if (*(char *)c == 't')
			bit_flags |= 16;
		((*(char *)&c)++);
	}
	return (bit_flags);
}

int main(int argc, const char **argv)
{
	t_ls	utils;
	char	*ptr;
	char	*hold_flags;
	int		i;
	char	*flags;
	flags = ft_strnew(MAX_FLAGS);

	vec_new(&utils.v_paths, 1, 256 * (argc - 1));
	i = 0;
	while (++i < argc)
	{
		ptr = (char *)argv[i];
		if (argv[i][0] == '-')
		{
			ptr++;
			hold_flags = get_flags(ptr); //can i do this with strupdate?
			ft_strcat(flags, hold_flags);
			free(hold_flags);
		}
		else
			vec_push(&utils.v_paths, ptr);
	}
	ft_printf("%s\n", flags);
	uint8_t bit_flags = turn_on_bits(flags);
	ft_printf("%b\n", bit_flags);
	free(flags);
	vec_iter(&utils.v_paths, print_str);
	vec_free(&utils.v_paths);
	return (0);
}
