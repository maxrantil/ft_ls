/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:52:50 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/14 11:03:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_utils(t_ls *utils)
{
	vec_new(&utils->v_input_paths, 0, MAX_PATH);
	vec_new(&utils->v_input_files, 0, MAX_PATH);
	vec_new(&utils->v_input_errors, 0, MAX_PATH);
	utils->input_files_stdout_c = 0;
	utils->flags_flag = 0;
}

void	init_flag_struct(t_flagvars *flagst, char *str)
{
	ft_memset(flagst->int_flags, 0, MAX_FLAGS);
	flagst->ret_str = ft_strnew(MAX_FLAGS);
	flagst->i = 0;
	flagst->ret_i = 0;
	flagst->n = ft_strlen(str);
}

void	init_data(t_data *data)
{
	data->total = 0;
	data->links_len = 0;
	data->owner_len = 0;
	data->group_len = 0;
	data->major_len = 0;
	data->size_len = 0;
}
