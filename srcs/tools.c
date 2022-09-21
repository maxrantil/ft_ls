/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:02 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/21 18:00:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	is_bit_set(unsigned int bit_str, unsigned int value)
{
	if (bit_str & value)
		return (1);
	return (0);
}

void	pathcat(char *path, char *file_name, char *base_path)
{
	if (base_path)
		ft_strcpy(path, base_path);
	ft_strcat(path, "/");
	ft_strcat(path, file_name);
}

char	*put_path_infront_of_file(t_ls *u, size_t i)
{
	char	*file_with_path;

	if (u->v_input_paths.len)
	{
		file_with_path = ft_strjoin((char *)vec_get(&u->v_input_paths, i), "/");
		file_with_path = ft_strupdate(file_with_path, u->dirp->d_name);
		return (file_with_path);
	}
	return (u->dirp->d_name);
}

int	check_flag_a(t_ls *utils, struct dirent *dirp)
{
	return (!is_bit_set(utils->bit_flags, A_FLAG) && \
	dirp->d_name[0] == '.');
}

void	flag_recurse(t_ls *utils)
{
	size_t	i;

	i = 0;
	while (i < utils->v_input_paths.len)
	{
		exec_flag_recurse(utils, (char *)vec_get(&utils->v_input_paths, i), i);
		i++;
	}	
}
