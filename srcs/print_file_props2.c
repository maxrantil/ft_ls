/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_props2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:57:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/09 19:03:29 by mrantil          ###   ########.fr       */
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
		ft_printf(" %-*s ", data->owner_len, pwd->pw_name);
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

void	print_file_props2(struct stat statbuf, t_data *data, size_t ret)
{
	ft_printf("  %*d", ft_intlen((long)data->links_len), statbuf.st_nlink);
	print_owner(statbuf, data);
	print_group(statbuf, data);
	if (ret == 2)
	{
		ft_printf("   %*ld,", ft_intlen((long)data->major_len), (long)major(statbuf.st_rdev));
		if ((long)minor(statbuf.st_rdev) > 999)
			ft_printf(" %#010lx", (long)minor(statbuf.st_rdev));
		else
			ft_printf("%*ld", 4, (long)minor(statbuf.st_rdev));
	}
	else if (data->major_len)
		ft_printf("    %*d", ft_intlen((long)data->major_len) + 4, statbuf.st_size);
	else
		ft_printf("  %*d", ft_intlen((long)data->size_len), statbuf.st_size);
	print_time(statbuf);
}
