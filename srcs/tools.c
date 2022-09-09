/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:01:02 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/09 19:01:31 by mrantil          ###   ########.fr       */
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

char	*put_path_infront_of_file(t_ls *utils, size_t i)
{
	char	*file_with_path;

	if (utils->v_input_paths.len)
	{
		file_with_path = ft_strjoin((char *)vec_get(&utils->v_input_paths, i), "/");
		file_with_path = ft_strupdate(file_with_path, utils->dirp->d_name);
		return (file_with_path);
	}
	return (utils->dirp->d_name);
}

void	init_data(t_data *data)
{
	data->total = 0;
	data->links_len = 0;			///can i memset the whole struct?
	data->owner_len = 0;
	data->group_len = 0;
	data->major_len = 0;
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
	if (major(statbuf.st_rdev) > data->major_len)
		data->major_len = major(statbuf.st_rdev);
	if (statbuf.st_size > data->size_len)
		data->size_len = statbuf.st_size;
}

int	check_flag_a(t_ls *utils, struct dirent *dirp)
{
	return (!ft_strcmp(dirp->d_name, ".") \
			|| !ft_strcmp(dirp->d_name, "..") \
			|| (!is_bit_set(utils->bit_flags, A_FLAG) \
				&& dirp->d_name[0] == '.'));
}