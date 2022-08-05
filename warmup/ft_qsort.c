/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:49:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/12 15:49:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_qsort(const char **str)
{
	int		i;
	int		j;
	char	temp[50];

	i = 0;
	while (str[i]) ///need to malloc for strlen of the longest to fit them. unsigned char d_namlen gives strlen
	{
		j = i + 1;
    	while (str[j])
		{
        	if (ft_strcmp(str[i], str[j]) > 0)
			{
            	ft_strcpy(temp, str[i]);
            	ft_strcpy((char *)str[i], str[j]);
				ft_strcpy((char *)str[j], temp);
			}
			++j;
		}
		++i;
	}
	i = 0;
	while (str[i])
      ft_printf("%s\n", str[i++]);
   return 0;
}
