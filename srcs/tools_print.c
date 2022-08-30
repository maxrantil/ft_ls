/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:59:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/30 16:11:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*no_path(char *file_with_path)
{
	size_t	n;

	n = ft_strlen(file_with_path);
	while (n > 0 && file_with_path[n] != '/')
		n--;
	if ((n == 0 && file_with_path[n] != '/') || n == ft_strlen(file_with_path))
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

	static void	print_stat(t_ls *utils, t_vec *v_files, size_t i, int total)
	{
		char	path[MAX_PATH];
		char	link_buf[MAX_PATH];
		size_t	link;

		ft_bzero(path, MAX_PATH);
		if ((utils->v_input_paths.len > 1 && !is_bit_set(utils->bit_flags, CAPITAL_R)) \
			|| (utils->v_input_paths.len && utils->v_input_files.len == utils->input_files_stdout_c))
			ft_printf("%s:\n", (char *)vec_get(&utils->v_input_paths, i));
		if (!utils->v_input_files.len)
			ft_printf("total: %d\n", total / 2);
		i = 0;
		while (i < v_files->len)
		{
			ft_strcpy(path, (char *)vec_get(v_files, i));
			lstat(path, &utils->statbuf);
			link = print_file_props(utils->statbuf);
			if (utils->v_input_files.len)
			{
				ft_printf("%s\n", path);
				if (utils->v_input_files.len == 1 && utils->v_input_paths.len)
					ft_putchar('\n');
				//utils->v_input_files.len--;														//can this be better controlled?
				utils->input_files_stdout_c++;														//can this be better controlled?
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
		if (utils->v_input_paths.len && i != utils->v_input_paths.len - 1)
			ft_putchar('\n');
}

static void	print_files(t_ls *utils, t_vec *v_files, size_t i)
{	
	char	file[MAX_FILENAME];
	size_t	term_len;
	size_t	len_count;

	len_count = 0;
	term_len = window_size() - 50;
	ft_bzero(file, MAX_FILENAME);
	if (utils->v_input_paths.len > 1 && !utils->v_input_files.len && !is_bit_set(utils->bit_flags, CAPITAL_R))
		ft_printf("%s:\n", (char *)vec_get(&utils->v_input_paths, i));
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

void	print_it(t_ls *utils, t_vec v_files, size_t i, int total)
{
	sort_it(&v_files, utils->bit_flags); 				//al thses inside at the top of the print function
	if (is_bit_set(utils->bit_flags, L_FLAG))
		print_stat(utils, &v_files, i, total);
	else
		print_files(utils, &v_files, i);
}
