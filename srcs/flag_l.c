/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:49:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/15 09:25:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_permissions(struct stat statbuf)
{
	ft_printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    ft_printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");	
}

void	print_nbr_hlinks(struct stat statbuf)
{
	ft_printf(" %i", statbuf.st_nlink);
}

void	print_owner(struct stat statbuf)
{
	struct passwd *pwd;
	
	pwd = getpwuid(statbuf.st_uid);
	if (pwd == NULL)
    	perror("getpwuid");
	else
    	ft_printf(" %s\t", pwd->pw_name);
}

void	print_group(struct stat statbuf)
{
	struct group *grp;
	
	grp = getgrgid(statbuf.st_gid);
	if (grp == NULL)
    	perror("getgrgid");
	else
    	ft_printf(" %-s\t", grp->gr_name);
}

void	print_time(struct stat statbuf)
{
	char	*mtime;
	
	mtime = ft_memalloc(ft_strlen(ctime(&statbuf.st_mtime)));
	ft_strcpy(mtime, ctime(&statbuf.st_mtime));
	ft_printf(" %.12s ", &(mtime[ft_strlen(mtime) - 21]));
	free(mtime);
}

void	print_size(struct stat statbuf)
{
	ft_printf(" %-i\t", statbuf.st_size);
}

void	print_file_props(struct stat statbuf)
{		
    print_permissions(statbuf);
	print_nbr_hlinks(statbuf);
	print_owner(statbuf);
	print_group(statbuf);
	print_size(statbuf);
	print_time(statbuf);
}

void	flag_l(struct dirent *dirp, char *path)
{
	struct stat	statbuf;
	t_vec		v_files;
	DIR			*dp;
	int			total;
	size_t		file_count;

	file_count = count_files(path);
	vec_new(&v_files, 1, 256 * file_count);
	dp = open_path(path);
	total = 0;
	while ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strcmp(dirp->d_name, ".") == 0 || ft_strcmp(dirp->d_name, "..") == 0 || dirp->d_name[0] == '.') //hidden folders dont show(no -a flag)
			continue;
		if (!stat(dirp->d_name, &statbuf))
		{
			total += statbuf.st_blocks;
			vec_push(&v_files, dirp->d_name);
		}
		else
		{
			perror("stat");
			exit(1);
		}	
	}
	ft_printf("total: %d\n", total/2);
	vec_sort(&v_files, &cmpfunc_str);
	vec_iter(&v_files, print_stat);
	vec_free(&v_files);
	if (closedir(dp) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}
