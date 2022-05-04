/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:54:38 by mrantil           #+#    #+#             */
/*   Updated: 2022/05/04 19:35:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char		*st;
	size_t		sl;

	if (!s)
		return (NULL);
	while (ft_isspace(s))
		s++;
	sl = ft_strlen(s);
	if (*s)
		while (ft_isspace(&s[sl - 1]))
			sl--;
	st = ft_strsub(s, 0, sl);
	return (st);
}
