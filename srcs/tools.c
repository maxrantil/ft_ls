/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:02 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/30 17:49:51 by mrantil          ###   ########.fr       */
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
	//size_t	n;

	if (base_path)
		ft_strcpy(path, base_path);
	//n = ft_strlen(path);		do i need these?
	//if (path[n] != '\n')
		ft_strcat(path, "/");
	ft_strcat(path, file_name);
}

/* static void	edge_case1(char *path)
{
	size_t n;

	n = ft_strlen(path);
	if (path[n] != '/')
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
		ft_printf("ft_ls: cannot access '%s': ", path); //error here with wrong filename and no flag
		//edge_case1(path);
		perror("");
	}
	return (utils->dp[i]);
}

void	init_data(t_data *data)
{
	data->total = 0;
	data->links_len = 0;			///can i memset the who struct?
	data->owner_len = 0;
	data->group_len = 0;
	data->size_len = 0;
}

void	get_data(struct stat statbuf, t_data *data)
{
	struct passwd	*pwd;
	struct group	*grp;
	size_t			pw_len;
	size_t			gr_len;
	
	data->total += statbuf.st_blocks;
	if (statbuf.st_nlink > data->links_len)
		data->links_len = statbuf.st_nlink;
	pwd = getpwuid(statbuf.st_uid);
	pw_len = ft_strlen(pwd->pw_name);
	if (pw_len > data->owner_len)
		data->owner_len = pw_len;
	grp = getgrgid(statbuf.st_gid);
	gr_len = ft_strlen(grp->gr_name);
	if (gr_len > data->group_len)
		data->group_len = gr_len;
	if (statbuf.st_size > data->size_len)
		data->size_len = statbuf.st_size;
}