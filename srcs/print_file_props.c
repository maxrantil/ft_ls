/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_props.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:57:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/30 16:16:25 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	print_dir_permissions(struct stat statbuf)
{
	if (S_ISDIR(statbuf.st_mode))
		ft_putchar('d');
	else if (S_ISCHR(statbuf.st_mode))
		ft_putchar('c');
	else if (S_ISBLK(statbuf.st_mode))
		ft_putchar('b');
	else if (S_ISLNK(statbuf.st_mode))
	{
		ft_putchar('l');
		return (1);
	}
	else if (S_ISSOCK(statbuf.st_mode))
		ft_putchar('s');
	else if (S_ISFIFO(statbuf.st_mode))
		ft_putchar('p');
	else
		ft_putchar('-');
	return (0);
}

static void	print_usr_permissions(struct stat statbuf)
{
    if (statbuf.st_mode & S_IRUSR)
		ft_putchar('r');
	else
		ft_putchar('-');	
    if (statbuf.st_mode & S_IWUSR)
		ft_putchar('w');
	else
		ft_putchar('-');	
    if (statbuf.st_mode & S_IXUSR)
    	if (statbuf.st_mode & S_ISUID)
			ft_putchar('s');
		else
			ft_putchar('x');
    else if (statbuf.st_mode & S_ISUID)
			ft_putchar('S');
	else
		ft_putchar('-');	
}

static void	print_grp_permissions(struct stat statbuf)
{
	if (statbuf.st_mode & S_IRGRP)
		ft_putchar('r');
	else
		ft_putchar('-');
    if (statbuf.st_mode & S_IWGRP)
		ft_putchar('w');
	else
		ft_putchar('-');
    if (statbuf.st_mode & S_IXGRP)
    	if (statbuf.st_mode & S_ISGID)
			ft_putchar('s');
		else
			ft_putchar('x');
    else if (statbuf.st_mode & S_ISGID)
		ft_putchar('S');
	else
		ft_putchar('-');
}

static void	print_oth_permissions(struct stat statbuf)
{
	if (statbuf.st_mode & S_IROTH)
		ft_putchar('r');
	else
		ft_putchar('-');
    if (statbuf.st_mode & S_IWOTH)
		ft_putchar('w');
	else
		ft_putchar('-');
    if (statbuf.st_mode & S_IXOTH)
    	if (statbuf.st_mode & S_ISVTX)
			ft_putchar('T');
		else
			ft_putchar('x');
    else if (statbuf.st_mode & S_ISVTX)
		ft_putchar('t');
	else
		ft_putchar('-');
}

static void	print_nbr_hlinks(struct stat statbuf)
{
	ft_printf(" %*i", 3, statbuf.st_nlink);
}

static void	print_owner(struct stat statbuf)
{
	struct passwd	*pwd;

	pwd = getpwuid(statbuf.st_uid);
	if (pwd == NULL)
		perror("getpwuid");
	else
		ft_printf(" %s\t", pwd->pw_name);
}

static void	print_group(struct stat statbuf)
{
	struct group	*grp;

	grp = getgrgid(statbuf.st_gid);
	if (grp == NULL)
		perror("getgrgid");
	else
		ft_printf(" %-s\t", grp->gr_name);
}

static void	print_size(struct stat statbuf)
{
	ft_printf(" %-*i", 8, statbuf.st_size);
}

static void	print_time(struct stat statbuf)
{
	char	*mtime;

	mtime = ft_memalloc(ft_strlen(ctime(&statbuf.st_mtime)));
	ft_strcpy(mtime, ctime(&statbuf.st_mtime));
	ft_printf(" %.12s ", &(mtime[ft_strlen(mtime) - 21]));
	free(mtime);
}

size_t	print_file_props(struct stat statbuf)
{
	size_t	ret;
	
	ret = print_dir_permissions(statbuf);
	print_usr_permissions(statbuf);
	print_grp_permissions(statbuf);
	print_oth_permissions(statbuf);
	print_nbr_hlinks(statbuf);
	print_owner(statbuf);
	print_group(statbuf);
	print_size(statbuf);
	print_time(statbuf);
	return (ret);
}
