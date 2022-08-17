/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:12:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/17 12:52:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H

# include "libft.h"
# include "ft_printf.h"
# include "vec.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define LS_FLAGS "alrRt"
# define MAX_FLAGS 5
# define MAX_FILENAME 256
# define MAX_PATH 1048

typedef enum e_flags
{
	NULL_FLAG = 0,
	A = 1,
	L = 2,
	R = 4,
	CAPITAL_R = 8,
	T = 16
}			t_flags;

typedef struct s_ls
{
	struct	dirent	*dirp;
	t_vec			v_paths;
	DIR				**dp;
	uint8_t			bit_flags;
}					t_ls;

void	work_data(t_ls *utils, char *flags);
void	exec_flag_null(t_ls *utils);
void	exec_flag_l(t_ls *utils);
void	exec_flag_recurse(struct dirent	*dirp, char *base_path);

/*
**	Tools
*/

DIR*	open_path(const char *str);
void	usage(int status);
size_t	count_files(char *dir_name);
void	print_files(t_ls *utils, t_vec *v_files, size_t i);

/*
**	Vec Tools
*/

int		cmpfunc_str(void *a, void *b);
void	print_str(void *src);
void	print_stat(void *src);
void	print_file_props(struct stat statbuf);

#endif
