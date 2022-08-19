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

static char	*put_path_infront_of_file(t_ls *utils, size_t i)
{
	char	*file_with_path;

	if (utils->v_paths.len)
	{
		file_with_path = ft_strjoin((char *)vec_get(&utils->v_paths, i), "/");
		file_with_path = ft_strupdate(file_with_path, utils->dirp->d_name);
		return (file_with_path);
	}
	else
		return (utils->dirp->d_name);
}

static void	flag_l(t_ls *utils, size_t i)
{
	struct stat	statbuf;
	t_vec		v_files;
	char		*file;
	int			total;

	vec_new(&v_files, 0, MAX_FILENAME);
	total = 0;
	while ((utils->dirp = readdir(utils->dp[i])) != NULL)
	{
		file = put_path_infront_of_file(utils, i); 
		if (utils->bit_flags ^ A && utils->dirp->d_name[0] == '.')
			continue ;
		if (!stat(file, &statbuf))
		{
			total += statbuf.st_blocks;
			if (vec_push(&v_files, file) < 0)
			{
				perror("vec_push, flag_l");
				exit(1);
			}
		}
		else
		{
			ft_printf("'%s' is not in: ", file);
			perror("stat in flag_l");
			exit(1);
		}
		if (utils->v_paths.len)
			ft_strdel(&file);
	}
	ft_printf("total: %d\n", total/2);
	vec_sort(&v_files, &cmpfunc_str);
	print_files_with_stat(statbuf, utils, &v_files, i);
	vec_free(&v_files);
	if (closedir(utils->dp[i]) < 0)
	{
		perror("can't close directory");
		exit(1);
	}
}

void	exec_flag_l(t_ls *utils)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!utils->v_paths.len)
		flag_l(utils, i);
	else
		vec_sort(&utils->v_paths, cmpfunc_str);
	while (i < utils->v_paths.len)
	{
		while (j < utils->v_paths.len)
		{
			utils->dp[j] = open_path(utils, j);
			j++;
		}
		if (utils->dp[i])
			flag_l(utils, i);
		i++;
	}
}
