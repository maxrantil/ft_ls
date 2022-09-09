/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:12:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/09 21:02:41 by mrantil          ###   ########.fr       */
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
# include <sys/sysmacros.h>

# define NANOTIME st_mtim.tv_nsec
# endif

# ifdef __APPLE__
# define NANOTIME st_mtimespec.tv_nsec
# endif

# define LS_FLAGS "alrRt"
# define MAX_FLAGS 5
# define MAX_FILENAME 256 + 6
# define MAX_PATH 1048

typedef enum e_flags
{
	NULL_FLAG = 0b00000,
	A_FLAG = 0b00001,
	L_FLAG = 0b00010,
	R_FLAG = 0b00100,
	CAPITAL_R = 0b01000,
	T_FLAG = 0b10000
}			t_flags;

typedef struct s_ls
{
	struct dirent	*dirp;
	//struct stat		statbuf;
	t_vec			v_input_paths;
	t_vec			v_input_files;
	t_vec			v_input_errors;
	size_t			input_files_stdout_c;
	uint8_t			bit_flags;
}					t_ls;

typedef struct s_data
{
	size_t	total;
	size_t	links_len;
	size_t	owner_len;
	size_t	group_len;
	long	major_len;
	long	size_len;
}			t_data;

void	work_input(t_ls *utils, char *flags);
void	flag_null(t_ls *utils);
void	flag_l(t_ls *utils);
void	exec_flag_l(t_ls *utils, size_t i);

void	flag_recurse(t_ls *utils);
void	exec_flag_recurse(t_ls *utils, char *input_path, size_t i); 
void	get_dirs_recurse(t_ls *utils, char *input_path, size_t i);

/*
**	Tools
*/
int		is_bit_set(unsigned int value, unsigned int bit_str);
void	pathcat(char *path, char *file_name, char *base_path);
char	*put_path_infront_of_file(t_ls *utils, size_t i);
DIR		*open_path(t_ls *utils, size_t j);
void	init_data(t_data *data);
void	get_data(char *file, t_data *data);
int		check_flag_a(t_ls *utils, struct dirent *dirp);

/*
**	Tools Print
*/

void	print_newline_and_path(t_ls *utils, char *path, size_t i);
void	print_error(char *path);
void	print_files(t_ls *utils, t_vec *v_files, size_t i);
void	sort_and_print_it(t_ls *utils, t_vec v_files, size_t i);
size_t	print_file_props1(char *file, t_data *data);
void	print_file_props2(struct stat *statbuf, t_data *data, size_t ret);

/*
**	Tools Vec
*/
void	sort_it(t_vec *vec_to_sort, unsigned int bit_str);
void	print_errors(t_vec error_vec);

#endif
