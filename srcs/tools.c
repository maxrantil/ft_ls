/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:02 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:01:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_bit_set(unsigned int bit_str, unsigned int value)
{
	if (bit_str & value)
		return (1);
	return (0);
}

/* static void	edge_case1(char *path)
{
	size_t n;

	n = ft_strlen(path);
	if (path[n != '/'])
		ft_printf("ft_ls: %s ", path);
	else
		ft_printf("ft_ls: "); //newline?
} */

DIR	*open_path(t_ls *utils, size_t i)
{
	char	path[MAX_PATH];

	ft_strcpy(path, (const char *)vec_get(&utils->v_input_paths, i));
	utils->dp[i] = opendir(path);
	if (!utils->dp[i])
	{
		ft_printf("ft_ls: cannot access '%s': ", path);
		//edge_case1(path);
		perror("");
	}
	return (utils->dp[i]);
}
