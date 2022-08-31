/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_props2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:57:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/31 12:57:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_owner(struct stat statbuf, t_data *data)
{
	struct passwd	*pwd;

	pwd = getpwuid(statbuf.st_uid);
	if (pwd == NULL)
		perror("getpwuid");
	else
		ft_printf(" %*s ", data->owner_len, pwd->pw_name);
}

static void	print_group(struct stat statbuf, t_data *data)
{
	struct group	*grp;

	grp = getgrgid(statbuf.st_gid);
	if (grp == NULL)
		perror("getgrgid");
	else
		ft_printf(" %-*s", data->group_len, grp->gr_name);
}

static void	print_time(struct stat statbuf)
{
	char	*mtime;

	mtime = ft_memalloc(ft_strlen(ctime(&statbuf.st_mtime)));
	ft_strcpy(mtime, ctime(&statbuf.st_mtime));
	ft_printf(" %.12s ", &(mtime[ft_strlen(mtime) - 21]));
	free(mtime);
}

void	print_file_props2(struct stat statbuf, t_data *data)
{
	ft_printf("  %*i", ft_intlen((long)data->links_len), statbuf.st_nlink);
	print_owner(statbuf, data);
	print_group(statbuf, data);
	ft_printf("  %*d", ft_intlen((long)data->size_len), statbuf.st_size);
	print_time(statbuf);
}
