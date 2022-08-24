/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:00:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:14:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_str_asc(void *a, void *b)
{
	return (ft_strcmp((char *)a, (const char *)b));
}

static int	sort_str_desc(void *a, void *b)
{
	return (ft_strcmp((char *)b, (const char *)a));
}

static int	sort_str_mtime(void *a, void *b)
{
	struct stat	a_statbuf;
	struct stat	b_statbuf;

	stat((char *)a, &a_statbuf);
	stat((char *)b, &b_statbuf);
	return (a_statbuf.st_mtime < b_statbuf.st_mtime);
}

//this need to be checked on iMac, works with -lt but not only -t??
void	sort_it(t_vec *vec_to_sort, unsigned int bit_str)
{
	if (is_bit_set(bit_str, T_FLAG))
		vec_sort(vec_to_sort, &sort_str_mtime);
	if (is_bit_set(bit_str, R_FLAG))
		vec_sort(vec_to_sort, &sort_str_desc);
	else
		vec_sort(vec_to_sort, &sort_str_asc);
}
