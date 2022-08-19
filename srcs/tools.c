#include "ft_ls.h"

char	*put_path_infront_of_file(t_ls *utils, size_t i)
{
	char	*file_with_path;

	if (utils->v_paths.len)
	{
		file_with_path = ft_strjoin((char *)vec_get(&utils->v_paths, i), "/");
		file_with_path = ft_strupdate(file_with_path, utils->dirp->d_name);
		return (file_with_path);
	}
	return (utils->dirp->d_name);
}

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

DIR		*open_path(t_ls *utils, size_t i)
{
	char	path[MAX_PATH];

	if (i == 9999) // this is my drunken solution, might need to think it over again
	{
		ft_strcpy(path, ".");; //is this okey??? or do i need to malloc for it?
		i = 0;
	}
	else
		ft_strcpy(path, (const char *)vec_get(&utils->v_paths, i));
	utils->dp[i] = opendir(path);
	if (!utils->dp[i])
	{
		ft_printf("ft_ls: cannot access '%s': ", path);
		perror("");
		++utils->opendir_error_count;
	}
	return (utils->dp[i]);
}

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
	if (utils->v_paths.len != 0 && i != utils->opendir_error_count - utils->v_paths.len - 1) // fix this later
		write(1, "\n\n", 2);
	else
		write(1, "\n", 1);
}

static char	*no_path(char *file_with_path)
{
	size_t n;

	n = ft_strlen(file_with_path);
	while (file_with_path[n] != '/')
		n--;
	return (&file_with_path[++n]);
}

void	print_files_with_stat(struct stat statbuf, t_ls *utils, t_vec *v_files, size_t i)
{
	if (utils->v_paths.len > 1)
		ft_printf("%s:\n", (char *)vec_get(&utils->v_paths, i));
	for (size_t x = 0; x < v_files->len; x++)
	{
		if (!stat((const char *)vec_get(v_files, x), &statbuf))
		{
			print_file_props(statbuf);
			if (utils->v_paths.len)
 		   		ft_printf("%s\n", no_path((char *)vec_get(v_files, x)));
			else
 		   		ft_printf("%s\n", (char *)vec_get(v_files, x));
		}
		else
		{
			ft_printf("Error with '%s' is not in: ", (char *)vec_get(v_files, x));
			perror("stat in print_files_with_stat()");
			exit(1);
		}
	}
	if (utils->v_paths.len != 0 && i != utils->opendir_error_count - utils->v_paths.len - 1)
		write(1, "\n", 1);
}