/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:59:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 18:59:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	window_size(void)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	return (size.ws_col);
}

static void	output_files(t_ls *utils, t_print *print_data, t_vec *v_files, \
ssize_t i)
{
	if (utils->v_input_files.len != utils->input_files_stdout_c)
	{
		ft_printf("%s", (char *)vec_get(v_files, i));
		utils->input_files_stdout_c++;
	}
	else
		ft_strcat(print_data->file, no_path((char *)vec_get(v_files, i)));
	print_data->len_count += ft_strlen(print_data->file) + 2;
	if (print_data->len_count > print_data->term_len)
	{
		ft_putchar('\n');
		print_data->len_count = 0;
	}
	ft_printf("%-*s", ft_strlen(print_data->file) + 2, print_data->file);
	ft_bzero(print_data->file, ft_strlen(print_data->file));
}

void	print_files(t_ls *utils, t_vec *v_files, ssize_t i)
{	
	t_print	print_data;

	print_data.len_count = 0;
	print_data.term_len = window_size() - 50;
	ft_bzero(print_data.file, MAX_PATH);
	if (is_bit_set(utils->bit_flags, R_FLAG))
	{
		i = v_files->len - 1;
		while (i >= 0)
		{
			output_files(utils, &print_data, v_files, i);
			i--;
		}	
	}
	else
	{
		i = 0;
		while (i < (ssize_t)v_files->len)
		{
			output_files(utils, &print_data, v_files, i);
			i++;
		}	
	}
	ft_putchar('\n');
}
