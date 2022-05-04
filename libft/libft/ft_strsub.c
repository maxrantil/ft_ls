/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:31:50 by mrantil           #+#    #+#             */
/*   Updated: 2022/05/04 19:35:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ss;

	if (!s)
		return (NULL);
	i = 0;
	ss = (char *)malloc(sizeof(char) * len + 1);
	if (!ss)
		return (NULL);
	while (len--)
		ss[i++] = s[start++];
	ss[i] = '\0';
	return (ss);
}
