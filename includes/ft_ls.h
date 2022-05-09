/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:12:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/05/09 10:02:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_LS_H
# define FT_LS_H

# include "../libraries/includes/libft.h"
# include "../libraries/includes/ft_printf.h"

typedef struct			s_opt
{
	unsigned int		dir : 1;
	unsigned int		grpname : 1;
}						t_opt;

#endif
