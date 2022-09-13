/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 18:33:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//need more correct for iMac
static void	usage(int status)
{
	ft_printf("Usage: %s [-alrRt]... [FILE]...\n", "./ft_ls");
	exit(status);
}

static void	init_flag_struct(t_flagvars *flagst, char *str)
{
	ft_memset(flagst->int_flags, 0, MAX_FLAGS);
	flagst->ret_str = ft_strnew(MAX_FLAGS);
	flagst->i = 0;
	flagst->ret_i = 0;
	flagst->n = ft_strlen(str);
}

static char	*get_flags(char *str)
{
	t_flagvars	flagst;

	init_flag_struct(&flagst, str);
	while (flagst.i < flagst.n)
	{
		flagst.j = 0;
		while (flagst.j <= MAX_FLAGS)
		{
			if (LS_FLAGS[flagst.j] == str[flagst.i])
				break ;
			if (flagst.j == MAX_FLAGS)
				usage(1);
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

static char	*check_flags(char *ptr, char *flags)
{
	char	*temp;

	ptr++;
	temp = get_flags(ptr);
	ft_strcat(flags, temp);
	free(temp);
	return (flags);
}

static char	*get_input(t_ls *utils, const char **argv, int argc)
{
	struct stat	statbuf;
	char		*ptr;
	char		*flags;
	int			i;

	flags = ft_strnew(MAX_FLAGS);
	utils->flags_flag = 0;
	i = 0;
	while (++i < argc)
	{
		ptr = (char *)argv[i];
		if (!utils->flags_flag && argv[i][0] == '-' && ft_isalpha(argv[i][1]))	//change i to 1 and then the fix is there for iMac terminal flags
		{
			flags = check_flags(ptr, flags);
			utils->flags_flag = 1;
			continue ;
		}
		if (lstat(ptr, &statbuf) < 0)
			vec_push(&utils->v_input_errors, ptr);
		else if (S_ISDIR(statbuf.st_mode))
			vec_push(&utils->v_input_paths, ptr);
		else
			vec_push(&utils->v_input_files, ptr);
	}
	if (utils->v_input_errors.len)
		print_errors(utils->v_input_errors);
	return (flags);
}

static void	init_utils(t_ls *utils)
{
	vec_new(&utils->v_input_paths, 0, MAX_PATH);
	vec_new(&utils->v_input_files, 0, MAX_PATH);
	vec_new(&utils->v_input_errors, 0, MAX_PATH);
	utils->input_files_stdout_c = 0;
}

int	main(int argc, const char **argv)
{
	t_ls	utils;
	char	*flags;

	init_utils(&utils);
	flags = get_input(&utils, argv, argc);
	work_input(&utils, flags);
	return (0);
}
