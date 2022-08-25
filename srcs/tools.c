/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:02 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/25 16:53:08 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_bit_set(unsigned int bit_str, unsigned int value)
{
	if (bit_str & value)
		return (1);
	return (0);
}

static void	edge_case1(char *path)
{
	size_t	n;

	n = ft_strlen(path);
	if (path[n] != '/')
		ft_printf("ft_ls: %s: ", path);
	else
		ft_printf("ft_ls: ");
}

DIR	*open_path(t_ls *utils, size_t i)
{
	char	path[MAX_PATH];

	ft_strcpy(path, (const char *)vec_get(&utils->v_paths, i));
	//stat(path, &utils->statbuf);
	//f (S_ISDIR(utils->statbuf.st_mode))
		utils->dp[i] = opendir(path);
/* 	else
	{
		ft_printf("%-*s", 2, path);
		return (utils->dp[i] = NULL);
	} */
	if (!utils->dp[i])
	{
		//ft_printf("ft_ls: cannot access '%s': ", path);
		edge_case1(path);
		perror("");
	}
	return (utils->dp[i]);
}
