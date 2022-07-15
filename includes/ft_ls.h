/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:12:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/15 15:18:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H

# include "libft.h"
# include "ft_printf.h"
# include "vec.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_file
{
	int		f_count;
	int		f_len;
	int		f_hlinks;
	int		f_size;
	char	*f_permissions;
	char	*f_owner;
	char	*f_group;
	char	*f_time;
}				t_file;

typedef struct s_dir
{
	t_file	*file;
	char	*base_path;
}				t_dir;

void	noflag(struct dirent *dirp, const char *path);
void	flag_l(struct dirent *dirp);
void	flag_recurse(char *base_path);

/*
**	Tools
*/
DIR*	open_path(const char *str);
int		cmpfunc_str(void *a, void *b);
void	print_str(void *src);

#endif
