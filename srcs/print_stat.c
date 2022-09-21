/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:59:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/21 16:25:35 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_data	padding(t_ls *utils, t_vec *v_files, t_data data)
{
	size_t	i;

	i = 0;
	while (i < v_files->len)
	{
		get_data((char *)vec_get(v_files, i), &data);
		i++;
	}
	if (utils->v_input_paths.len && v_files->len \
	&& utils->v_input_files.len == utils->input_files_stdout_c)
		ft_printf("total %d\n", data.total);
	return (data);
}

static void	if_link(size_t link, char *path)
{
	char	link_buf[MAX_PATHLEN];

	if (link)
	{
		ft_bzero(link_buf, MAX_PATHLEN);
		if (readlink(path, link_buf, MAX_PATHLEN) > 0)
			ft_printf(" -> %s", link_buf);
	}
}

static void	output_stat(t_ls *utils, t_printstat *printstat, \
t_vec *v_files, ssize_t i)
{
	ft_strcpy(printstat->path, (char *)vec_get(v_files, i));
	printstat->link = print_file_props1(printstat->path, &printstat->data);
	if (utils->v_input_files.len != utils->input_files_stdout_c)
	{
		ft_printf("%s", printstat->path);
		utils->input_files_stdout_c++;
	}
	else
		ft_printf("%s", no_path(printstat->path));
	if_link(printstat->link, printstat->path);
	ft_putchar('\n');
}

void	print_stat(t_ls *utils, t_vec *v_files, ssize_t i)
{
	t_printstat	printstat;

	ft_bzero(printstat.path, MAX_PATHLEN);
	init_data(&printstat.data);
	printstat.data = padding(utils, v_files, printstat.data);
	if (is_bit_set(utils->bit_flags, R_FLAG))
	{
		i = v_files->len - 1;
		while (i >= 0)
		{
			output_stat(utils, &printstat, v_files, i);
			i--;
		}	
	}
	else
	{
		i = 0;
		while (i < (ssize_t)v_files->len)
		{
			output_stat(utils, &printstat, v_files, i);
			i++;
		}
	}
}
