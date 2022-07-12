/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:12:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/12 12:37:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H

# include "libft.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_opt
{
	unsigned int		dir : 1;
	unsigned int		grpname : 1;
}						t_opt;

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
}				t_dir;

DIR*	open_path(const char *str);
void	flag_l(struct dirent *dirp);
void	flag_capital_r(char *base_path);


#endif
