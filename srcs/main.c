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

static void	init_ls(t_ls *utils)
{
	vec_new(&utils->v_paths, 1, MAX_PATH);
	utils->flags = ft_strnew(MAX_FLAGS);
	utils->bit_flags = 0;

}

static void	get_data(t_ls *utils, const char **argv, int argc)
{
	char	*ptr;
	char	*temp;
	int		i;

	i = 0;
	while (++i < argc)
	{
		ptr = (char *)argv[i];
		if (argv[i][0] == '-')
		{
			ptr++;
			temp = get_flags(ptr);
			ft_strcat(utils->flags, temp);
			free(temp);
		}
		else
			vec_push(&utils->v_paths, ptr);
	}
	utils->dp = (DIR **)malloc(sizeof(DIR *) * utils->v_paths.len);
}

int main(int argc, const char **argv)
{
	t_ls	utils;

	init_ls(&utils);
	get_data(&utils, argv, argc);
	work_data(&utils);
	return (0);
}
