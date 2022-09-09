/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:59:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/09 17:18:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_newline_and_path(t_ls *utils, char *path, size_t i)
{
	if (i != 0 || (i == 0 && utils->v_input_files.len))
		ft_putchar('\n');
	if (utils->v_input_errors.len || utils->v_input_paths.len > 1 || \
		(utils->v_input_paths.len && utils->v_input_files.len && \
		utils->v_input_files.len == utils->input_files_stdout_c))
			ft_printf("%s:\n", path);
}

void	print_error(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
			ft_printf("ft_ls: : ");	
		else
			ft_printf("ft_ls: %s: ", path);
		perror("");
}

static char	*no_path(char *file_with_path)
{
	size_t	n;

	if (!file_with_path)
		return (NULL);
	n = ft_strlen(file_with_path) - 1;
	while (n > 0 && file_with_path[n] != '/')
		n--;
	if (n == 0)// && file_with_path[n] != '/')
		return (&file_with_path[n]);
	return (&file_with_path[++n]);
}

static size_t	window_size(void)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	return (size.ws_col);
}

static void	print_stat(t_ls *utils, t_vec *v_files, t_data *data, size_t i)
{
	char	path[MAX_PATH];
	char	link_buf[MAX_PATH];
	size_t	link;

	ft_bzero(path, MAX_PATH);
	if (!utils->v_input_files.len)
		ft_printf("total: %d\n", data->total);
	i = 0;
	while (i < v_files->len)
	{
		ft_strcpy(path, (char *)vec_get(v_files, i));
		lstat(path, &utils->statbuf);
		link = print_file_props1(utils->statbuf, data);
		if (utils->v_input_files.len)
		{
			ft_printf("%s\n", path);
			if (utils->v_input_files.len == 1 && utils->v_input_paths.len)
				ft_putchar('\n');
			utils->input_files_stdout_c++;
		}
		else
			ft_printf("%s", no_path(path));
		if (link)
		{
			ft_bzero(link_buf, MAX_PATH);
			if (readlink(path, link_buf, MAX_PATH) > 0)
				ft_printf(" -> %s", link_buf);	
		}
		ft_putchar('\n');
		i++;
	}
}

void	print_files(t_vec *v_files, size_t i)
{	
	char	file[MAX_PATH];
	size_t	term_len;
	size_t	len_count;

	len_count = 0;
	term_len = window_size() - 50;
	ft_bzero(file, MAX_PATH);
	i = 0;
	while (i < v_files->len)
	{
		ft_strcat(file, no_path((char *)vec_get(v_files, i)));
		len_count += ft_strlen(file) + 2;
		if (len_count > term_len)
		{
			ft_putchar('\n');
			len_count = 0;
		}
		ft_printf("%-*s", ft_strlen(file) + 2, file);
		ft_bzero(file, ft_strlen(file));
		i++;
	}
	ft_putchar('\n');
}

void	sort_and_print_it(t_ls *utils, t_vec v_files, t_data *data, size_t i)
{
	sort_it(&v_files, utils->bit_flags);
	if (is_bit_set(utils->bit_flags, L_FLAG))
		print_stat(utils, &v_files, data, i); 					//noneed to send i here
	else
		print_files(&v_files, i);
}
