/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:00:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 15:07:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_str_asc(void *a, void *b)
{
	return (ft_strcmp((char *)a, (const char *)b));
}

/* static int	sort_str_desc(void *a, void *b)
{
	return (ft_strcmp((char *)b, (const char *)a));
} */

/* static void	rev_sort(void *vec)
{
	char	*a;
	char	*b;
	
	a = vec_get(vec, 1);
	b = vec_get(vec, 2);
	ft_swap((int *)a, (int *)b);
} */

static int	sort_str_mtime(void *a, void *b)
{
	struct stat		statbuf;
	long long		times[4];
	long long		ret;

	lstat((char *)a, &statbuf);
	times[0] = statbuf.st_mtime;
	times[1] = statbuf.NANOTIME;
	lstat((char *)b, &statbuf);
	times[2] = statbuf.st_mtime;
	times[3] = statbuf.NANOTIME;
	ret = times[2] - times[0];
	if (ret)
		return (ret);
	ret = times[3] - times[1];
	if (ret)
		return (ret);
	return (ft_strcmp((char *)a, (const char *)b));
}
/* void reverse_array(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
	return ();
} */

void	reverse_sort(t_vec *vec_to_sort)
{
	size_t	n;
	size_t	start;	
	size_t	end;
	
	start = 0;
	end = vec_to_sort->len - 1;	
	n = vec_to_sort->len;
	if (n % 2)
		n -= 1;
	n /= 2;
/* 	while (n)
	{ */
		ft_swapstr(vec_get(vec_to_sort, start), vec_get(vec_to_sort, end));
/* 		start++;
		end--;
		n--;
	}	 */
}

void	sort_it(t_vec *vec_to_sort, unsigned int bit_str)
{
	vec_sort(vec_to_sort, &sort_str_asc);
	if (is_bit_set(bit_str, T_FLAG))
		vec_sort(vec_to_sort, &sort_str_mtime);
	if (is_bit_set(bit_str, R_FLAG))
		reverse_sort(vec_to_sort); 
}

void	print_errors(t_vec error_vec)
{
	size_t	i;

	i = 0;
	vec_sort(&error_vec, &sort_str_asc);
	while (i < error_vec.len)
	{
		ft_printf("ft_ls: %s: ", vec_get(&error_vec, i++));		//need som edge_case handeling here
		perror("");
	}	
}