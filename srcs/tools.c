#include "ft_ls.h"

void	usage(int status)
{
	ft_printf("Usage: %s [OPTION]... [FILE]...\n", "./ft_ls");
	ft_printf("\
	List information about the FILEs (the current directory by default).\n\
	Sort entries alphabetically if not -t is specified.\n");
	ft_printf("\
	-a	do not ignore entries starting with .\n\
	-l	use a long listing format\n\
	-r	reverse order while sorting\n\
	-R	list subdirectories recursively\n\
	-t	sort by modification time, newest first\n");
	exit(status);
}

DIR*	open_path(const char *str)
{
	DIR *dp;
	
	dp = opendir(str);
	if (!dp)
	{
		ft_printf("ft_ls: cannot access '%s': ", str);
		perror("");
		return NULL;
	}
	return (dp);
}

size_t count_files(char *dir_name)
{
	struct dirent	*dirp;
	DIR				*dp;
	size_t			file_count;

	file_count = 0;
	dp = open_path(dir_name);
	while ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strcmp(dirp->d_name, ".") == 0 || ft_strcmp(dirp->d_name, "..") == 0)
			continue ;
		++file_count;
	}
	free(dirp);
	free(dp);
	return (file_count);
}

/*
// BONUS		
*/

static size_t	window_size(void)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	return (size.ws_col);
}

void	print_files(t_ls *utils, t_vec *v_files, size_t i)
{	
	size_t	len_count;
	size_t	win_size;

	len_count = 0;
	win_size = window_size();
	if (utils->v_paths.len > 1)
		ft_printf("%s:\n", (char *)vec_get(&utils->v_paths, i));
	for (size_t x = 0; x < v_files->len; x++)
	{
		char *file = (char *)vec_get(v_files, x);
		len_count += ft_strlen(file) + 2;
		if (len_count > win_size)
		{
			write(1, "\n", 1);
			len_count = 0;
		} 
    	ft_printf("%-*s", ft_strlen(file) + 2, file);
	}
	if (i != utils->v_paths.len - 1)
		write(1, "\n\n", 2);
	else
		write(1, "\n", 1);
}