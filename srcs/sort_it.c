/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:00:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/14 12:01:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_str_asc(void *a, void *b)
{
	return (ft_strcmp((char *)a, (const char *)b));
}

static int	sort_str_mtime(void *a, void *b)
{
	struct stat		statbuf;
	long long		times[4];
	long long		ret;

	lstat((char *)a, &statbuf);
	times[0] = statbuf.st_mtime;
	times[1] = statbuf.st_mtimespec.tv_nsec;
	lstat((char *)b, &statbuf);
	times[2] = statbuf.st_mtime;
	times[3] = statbuf.st_mtimespec.tv_nsec;
	ret = times[2] - times[0];
	if (ret)
		return (ret);
	ret = times[3] - times[1];
	if (ret)
		return (ret);
	return (ft_strcmp((char *)a, (const char *)b));
}

void	sort_it(t_vec *vec_to_sort, unsigned int bit_str)
{
	vec_sort(vec_to_sort, &sort_str_asc);
	if (is_bit_set(bit_str, T_FLAG))
		vec_sort(vec_to_sort, &sort_str_mtime);
}

void	print_errors(t_vec error_vec)
{
	size_t	i;

	i = 0;
	vec_sort(&error_vec, &sort_str_asc);
	while (i < error_vec.len)
	{
		ft_printf("ft_ls: %s: ", vec_get(&error_vec, i++));
		perror("");
	}	
}
