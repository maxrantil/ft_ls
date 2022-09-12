/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:10:36 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 15:07:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
void	ft_swapstr(void **a, void **b)
{
	printf("a = %s\n", (char *)a);
	printf("b = %s\n", (char *)b);
	void	*temp;

	temp = (*a);
	(*a) = (*b);
	(*b) = temp;
	printf("a = %s\n", (char *)a);
	printf("b = %s\n", (char *)b);
}
