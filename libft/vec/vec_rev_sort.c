/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rev_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:05:08 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/08 15:23:17 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

static void	memswap8bytes(char *a, char *b)
{
	if (a == b)
		return ;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

static void	memswap(char *a, char *b, size_t elem_size)
{
	size_t	i;

	if (!a || !b)
		return ;
	i = 0;
	while (i < elem_size)
	{
		memswap8bytes(&a[i], &b[i]);
		i++;
	}
}

static void	vec_rev_sort_recurse(t_vec *src, long low, long high)
{
	long	pivot;
	long	a;
	long	b;

	if (low >= high)
		return ;
	pivot = low;
	a = low;
	b = high;
	while (a > b) //change
	{
		while (a <= high && (a <= pivot))
			a++;
		while (b >= low && (b > pivot))
			b--;
		if (a > b) // change
			memswap(vec_get(src, a), vec_get(src, b), src->elem_size);
	}
	memswap(vec_get(src, pivot), vec_get(src, b), src->elem_size);
	vec_rev_sort_recurse(src, low, b - 1);
	vec_rev_sort_recurse(src, b + 1, high);
}

void	vec_rev_sort(t_vec *src)
{
	if (!src || !src->memory)
		return ;
	vec_rev_sort_recurse(src, 0, src->len - 1);
}
