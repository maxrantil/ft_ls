/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:42:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/15 12:56:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_total(struct stat statbuf, t_data *data)
{
	data->total += statbuf.st_blocks;
	if (statbuf.st_nlink > data->links_len)
		data->links_len = statbuf.st_nlink;
}

static void	get_id(struct stat statbuf, t_data *data)
{
	struct passwd	*pwd;
	size_t			pw_len;

	pwd = getpwuid(statbuf.st_uid);
	if (pwd == NULL)
		pw_len = ft_intlen(statbuf.st_uid);
	else
		pw_len = ft_strlen(pwd->pw_name);
	if (pw_len > data->owner_len)
		data->owner_len = pw_len;
}

static void	get_group(struct stat statbuf, t_data *data)
{
	struct group	*grp;
	size_t			gr_len;

	grp = getgrgid(statbuf.st_gid);
	if (grp == NULL)
		gr_len = ft_intlen(statbuf.st_gid);
	else
		gr_len = ft_strlen(grp->gr_name);
	if (gr_len > data->group_len)
		data->group_len = gr_len;
}

static void	get_major_minor(struct stat statbuf, t_data *data)
{
	if (major(statbuf.st_rdev) > data->major_len)
		data->major_len = major(statbuf.st_rdev);
	if (statbuf.st_size > data->size_len)
		data->size_len = statbuf.st_size;
}

void	get_data(char *file, t_data *data)
{
	struct stat		statbuf;

	lstat(file, &statbuf);
	get_total(statbuf, data);
	get_id(statbuf, data);
	get_group(statbuf, data);
	get_major_minor(statbuf, data);
}
