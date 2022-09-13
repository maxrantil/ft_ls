/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:12:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/13 07:16:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

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

/* Major/Minor Numbers */
# ifdef __linux__
# include <sys/sysmacros.h>		//fix for eval but save for after eval

# define NANOTIME st_mtim.tv_nsec
# endif

# ifdef __APPLE__
# define NANOTIME st_mtimespec.tv_nsec
# endif

# define LS_FLAGS "alrRt"
# define MAX_FLAGS 5
/* the 8 is for getting the max strlen of a file on Mac */
# define MAX_FILENAME 256 + 8
# define MAX_PATH 1048

typedef enum e_flags
{
	NULL_FLAG	= 0b00000,
	A_FLAG		= 0b00001,
	L_FLAG		= 0b00010,
	R_FLAG		= 0b00100,
	CAPITAL_R	= 0b01000,
	T_FLAG		= 0b10000
}			t_flags;

typedef struct s_ls
{
	struct dirent	*dirp;
	t_vec			v_input_paths;
	t_vec			v_input_files;
	t_vec			v_input_errors;
	size_t			input_files_stdout_c;
	uint8_t			bit_flags;
	size_t			flags_flag;
}					t_ls;

typedef struct s_flagvars
{
	int		int_flags[MAX_FLAGS];
	char	*ret_str;
	int		i;
	int		j;
	int		ret_i;
	int		n;
}			t_flagvars;

typedef struct s_data
{
	size_t	total;
	size_t	links_len;
	size_t	owner_len;
	size_t	group_len;
	long	major_len;
	long	size_len;
}			t_data;

typedef struct s_print
{
	char	file[MAX_PATH];
	size_t	term_len;
	size_t	len_count;
}			t_print;

typedef struct s_printstat
{
	char	path[MAX_PATH];
	t_data	data;
	size_t	link;
}			t_printstat;

/*
**	Basics
*/
void	work_input(t_ls *utils, char *flags);
void	get_files(t_ls *utils, t_vec *v_files, size_t i);
void	get_files_from_path(t_ls *utils);
void	push_file(t_ls *utils, t_vec *v_files, size_t i);
void	flag_recurse(t_ls *utils);
void	exec_flag_recurse(t_ls *utils, char *input_path, size_t i);

/*
**	Tools
*/
int		is_bit_set(unsigned int value, unsigned int bit_str);
void	pathcat(char *path, char *file_name, char *base_path);
char	*put_path_infront_of_file(t_ls *utils, size_t i);
DIR		*open_path(t_ls *utils, size_t j);
void	get_data(char *file, t_data *data);
int		check_flag_a(t_ls *utils, struct dirent *dirp);

/*
**	Tools Print
*/
void	print_newline_and_path(t_ls *utils, char *path, size_t i);
void	print_error(char *path);
void	print_files(t_ls *utils, t_vec *v_files, ssize_t i);
void	print_stat(t_ls *utils, t_vec *v_files, ssize_t i);
void	sort_and_print_it(t_ls *utils, t_vec *v_files, size_t i);
size_t	print_file_props1(char *file, t_data *data);
void	print_file_props2(struct stat *statbuf, t_data *data, size_t ret);
char	*no_path(char *file_with_path);

/*
**	Sort
*/
void	sort_it(t_vec *vec_to_sort, unsigned int bit_str);
void	print_errors(t_vec error_vec);

#endif
