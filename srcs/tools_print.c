/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:59:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 19:16:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		ft_printf("ft_ls: : ");
	else
		ft_printf("ft_ls: %s: ", path);
	perror("");
}

char	*no_path(char *file_with_path)
{
	size_t	n;

	if (!file_with_path)
		return (NULL);
	n = ft_strlen(file_with_path) - 1;
	while (n > 0 && file_with_path[n] != '/')
		n--;
	if (n == 0)
		return (&file_with_path[n]);
	return (&file_with_path[++n]);
}

void	print_newline_and_path(t_ls *utils, char *path, size_t i)
{
	if (i != 0 || (i == 0 && (utils->v_input_files.len || \
	utils->v_input_paths.len > 1)))
		ft_putchar('\n');
	if (utils->v_input_errors.len || utils->v_input_paths.len > 1 || \
	(utils->v_input_files.len && \
	utils->v_input_files.len == utils->input_files_stdout_c) \
	|| (is_bit_set(utils->bit_flags, CAPITAL_R) && i != 0))
		ft_printf("%s:\n", path);
}

void	sort_and_print_it(t_ls *utils, t_vec v_files, size_t i)
{
	sort_it(&v_files, utils->bit_flags);
	if (is_bit_set(utils->bit_flags, L_FLAG))
		print_stat(utils, &v_files, i);
	else
		print_files(utils, &v_files, i);
}
