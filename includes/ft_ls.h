/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:12:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/15 16:32:00 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include "vec.h"
/* struct dirent */
# include <dirent.h>
/* struct stat */
# include <sys/stat.h>
/* minor and major numbers */
# include <sys/types.h>
/* window size */
# include <sys/ioctl.h>
/* perror() */
# include <stdio.h>
/* time() & ctime() */
# include <time.h>
/* struct passwd */
# include <pwd.h>
/* struct group */
# include <grp.h>

# define LS_FLAGS "alrRt"
# define MAX_FLAGS 5
# define MAX_FILENAME 255
# define MAX_PATH 1024
# define SIX_MONTHS_SEC 15778476

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

typedef struct s_flagvar
{
	int		int_flags[MAX_FLAGS];
	char	*ret_str;
	int		i;
	int		j;
	int		ret_i;
	int		n;
}			t_flagvar;

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
void	flag_recurse(t_ls *utils);
void	exec_flag_recurse(t_ls *utils, char *input_path, size_t i);
void	get_data(char *file, t_data *data);

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
void	usage(char c, int status);
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

/*
**	Init
*/
void	init_utils(t_ls *utils);
void	init_flag_struct(t_flagvar *flagst, char *str);
void	init_data(t_data *data);
void	free_vectors(t_ls *utils);

#endif
