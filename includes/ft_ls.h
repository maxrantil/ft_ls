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
	NULL_FLAG = 0b00000,
	A = 0b00001,
	L = 0b00010,
	R = 0b00100,
	CAPITAL_R = 0b01000,
	T = 0b10000
}			t_flags;

typedef struct s_ls
{
	struct dirent	*dirp;
	struct stat		statbuf;
	t_vec			v_paths;
	DIR				**dp;
	uint8_t			bit_flags;
}					t_ls;

void	work_data(t_ls *utils, char *flags);
void	print_file_props(struct stat statbuf);
void	flag_null(t_ls *utils);
void	flag_l(t_ls *utils);
void	flag_recurse(t_ls *utils);

/*
**	Tools
*/

int		is_bit_set(unsigned int value, unsigned int bit_str);
DIR*	open_path(t_ls *utils, size_t j);
size_t	count_files(t_ls *utils, size_t i);
void	print_it(t_ls *utils, t_vec v_files, size_t i, int total);
char	*no_path(char *file_with_path);
void	print_file_props(struct stat statbuf);

/*
**	Vec Tools
*/

void	sort_it(t_vec *vec_to_sort, unsigned int bit_str);
void	print_str(void *src);

#endif
