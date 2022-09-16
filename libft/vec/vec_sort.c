/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:05:08 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/16 12:08:35 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
// Create a function which takes in a function f determining order and 
// equality of the two elements passed as parameters and thus sorting
// the array accordingly from the smallest to the largest element.
*/
static void	memswap8bytes(unsigned char *a, unsigned char *b)
{
	if (a == b)
		return ;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

static void	memswap(unsigned char *a, unsigned char *b, size_t bytes)
{
	size_t	i;

	if (!a || !b)
		return ;
	i = 0;
	while (i < bytes)
	{
		memswap8bytes(&a[i], &b[i]);
		i++;
	}
}

static void	v_sort_recursive(t_vec *src, long low, long high, \
int (*f)(void *, void *))
{
	long	pivot;
	long	a;
	long	b;

	if (low >= high)
		return ;
	pivot = low;
	a = low;
	b = high;
	while (a < b)
	{
		while (a <= high && f(vec_get(src, a), vec_get(src, pivot)) <= 0)
			a++;
		while (b >= low && f(vec_get(src, b), vec_get(src, pivot)) > 0)
			b--;
		if (a < b)
			memswap(vec_get(src, a), vec_get(src, b), src->elem_size);
	}
	memswap(vec_get(src, pivot), vec_get(src, b), src->elem_size);
	v_sort_recursive(src, low, b - 1, f);
	v_sort_recursive(src, b + 1, high, f);
}

void	vec_sort(t_vec *src, int (*f)(void *, void *))
{
	if (!src || !src->memory)
		return ;
	v_sort_recursive(src, 0, src->len - 1, f);
}
