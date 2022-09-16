/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/16 10:54:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* compare input to string of valid flags in h-file */
static char	*check_flags(char *str)
{
	t_flagvar	flagst;

	init_flag_struct(&flagst, str);
	while (flagst.i < flagst.n)
	{
		flagst.j = 0;
		while (flagst.j <= MAX_FLAGS)
		{
			if (LS_FLAGS[flagst.j] == str[flagst.i])
				break ;
			if (flagst.j == MAX_FLAGS)
				usage(str[flagst.i], 1);
			flagst.j++;
		}
		if (!flagst.int_flags[flagst.j])
		{
			flagst.int_flags[flagst.j] = 1;
			flagst.ret_str[flagst.ret_i++] = str[flagst.i];
		}
		flagst.i++;
	}
	return (flagst.ret_str);
}

static char	*pre_check_flags(char *ptr, char *flags)
{
	char	*temp;

	ptr++;
	temp = check_flags(ptr);
	ft_strcat(flags, temp);
	free(temp);
	return (flags);
}

static void	push_to_vectors(t_ls *utils, char *ptr)
{
	struct stat	statbuf;

	if (lstat(ptr, &statbuf) < 0)
		vec_push(&utils->v_input_errors, ptr);
	else if (S_ISDIR(statbuf.st_mode))
		vec_push(&utils->v_input_paths, ptr);
	else
		vec_push(&utils->v_input_files, ptr);
}

static char	*get_flags(t_ls *utils, const char **argv, int argc, int i)
{
	char	*ptr;
	char	*flags;

	flags = ft_strnew(MAX_FLAGS);
	while (++i < argc)
	{
		ptr = (char *)argv[i];
		if (!utils->flags_flag && argv[i][0] == '-' && ft_isalpha(argv[i][1]))
		{
			flags = pre_check_flags(ptr, flags);
			continue ;
		}
		utils->flags_flag = 1;
		push_to_vectors(utils, ptr);
	}
	if (utils->v_input_errors.len)
		print_errors(utils->v_input_errors);
	return (flags);
}

int	main(int argc, const char **argv)
{
	t_ls	utils;
	char	*flags;
	int		i;

	init_utils(&utils);
	i = 0;
	flags = get_flags(&utils, argv, argc, i);
	work_input(&utils, flags);
	return (0);
}
