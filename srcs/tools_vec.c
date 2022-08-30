/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:00:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/30 11:51:40 by mrantil          ###   ########.fr       */
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
	struct stat	statbuf_a;
	struct stat	statbuf_b;
	long long	times[4];

	stat((char *)a, &statbuf_a);
	times[0] = statbuf_a.st_mtime;
	times[1] = statbuf_a.st_mtim.tv_nsec;
	stat((char *)b, &statbuf_b);
	times[2] = statbuf_b.st_mtime;
	times[3] = statbuf_b.st_mtim.tv_nsec;
//	ft_printf("0	=	%ld\n", times[0]);
//	ft_printf("1	=	%ld\n", times[1]);
	if (times[0] < times[2] || (times[0] == times[2] && times[1] < times[3]))			//look in school, can i do this in a return without if? can i do it with only nano seconds?
		return (1);
	return (0);
}
// st_atim.tv_nsec

//this need to be checked on iMac, works with -lt but not only -t??
void	sort_it(t_vec *vec_to_sort, unsigned int bit_str)
{
	vec_sort(vec_to_sort, &sort_str_asc);
	if (is_bit_set(bit_str, T_FLAG))
		vec_sort(vec_to_sort, &sort_str_mtime); //is this the right order?
	if (is_bit_set(bit_str, R_FLAG))
		vec_sort(vec_to_sort, &sort_str_desc);
}
