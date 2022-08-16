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

typedef struct s_ls
{
	struct	dirent	*dirp;
	t_vec			v_paths;
}					t_ls;

void	noflag(struct dirent *dirp, const char *path);
void	flag_l(struct dirent *dirp, char *path);
void	flag_recurse(struct dirent	*dirp, char *base_path);
size_t	window_size(void);

/*
**	Tools
*/
DIR*	open_path(const char *str);
int		cmpfunc_str(void *a, void *b);
void	print_str(void *src);
void	print_stat(void *src);
void	print_file_props(struct stat statbuf);
size_t	count_files(char *dir_name);

#endif
