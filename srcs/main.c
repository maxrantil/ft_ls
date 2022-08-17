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

static void	malloc_directory_ptr(t_ls *utils)
{
	if (!utils->v_paths.len)
	{
		utils->dp = (DIR **)malloc(sizeof(DIR *) * 1);
		utils->dp[0] = open_path(utils, 9999);
	}
	else
		utils->dp = (DIR **)malloc(sizeof(DIR *) * utils->v_paths.len);
}

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
		if (argv[i][0] == '-' && ft_isalpha(argv[i][1]))
		{
			ptr++;
			temp = get_flags(ptr);
			ft_strcat(flags, temp);
			free(temp);
		}
		else
			vec_push(&utils->v_paths, ptr);
	}
	return (flags);
}

static void	init_ls(t_ls *utils)
{
	vec_new(&utils->v_paths, 1, MAX_PATH);
	utils->bit_flags = 0;

}

int main(int argc, const char **argv)
{
	t_ls	utils;
	char	*flags;

	init_ls(&utils);
	flags = get_data(&utils, argv, argc);
	malloc_directory_ptr(&utils);
	work_data(&utils, flags);
	return (0);
}
