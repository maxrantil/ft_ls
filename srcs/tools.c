/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:02 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/13 08:39:49 by mrantil          ###   ########.fr       */
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

void	get_data(char *file, t_data *data)
{
	struct stat		statbuf;
	struct passwd	*pwd;
	struct group	*grp;
	size_t			pw_len;
	size_t			gr_len;

	lstat(file, &statbuf);
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
	if (major(statbuf.st_rdev) > data->major_len)
		data->major_len = major(statbuf.st_rdev);
	if (statbuf.st_size > data->size_len)
		data->size_len = statbuf.st_size;
}

int	check_flag_a(t_ls *utils, struct dirent *dirp)
{
	return (!is_bit_set(utils->bit_flags, A_FLAG) && \
	dirp->d_name[0] == '.');
}
