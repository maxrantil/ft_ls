#include "ft_ls.h"

static size_t	window_size(void)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	return (size.ws_col);
}

static void	print_files(t_ls *utils, t_vec *v_files, size_t i)
{	
	char	*file;
	size_t	len_count;
	size_t	win_size;
	size_t	y;

	len_count = 0;
	y = 0;
	win_size = window_size();
	if (utils->v_paths.len > 1 && !is_bit_set(utils->bit_flags, CAPITAL_R))
		ft_printf("%s:\n", (char *)vec_get(&utils->v_paths, i));
	while (y < v_files->len)
	{
		file = no_path((char *)vec_get(v_files, y));
		len_count += ft_strlen(file) + 5;
		if (len_count >= win_size)
		{
			write(1, "\n", 1);
			len_count = 0;
		}
   		ft_printf("%-*s", ft_strlen(file) + 2, file);
		y++;
	}
	write(1, "\n", 1);
}

static void	print_stat(t_ls *utils, t_vec *v_files, size_t i, int total)
{
	size_t	y;

	y = 0;
	if (utils->v_paths.len > 1 && !is_bit_set(utils->bit_flags, CAPITAL_R))
		ft_printf("%s:\n", (char *)vec_get(&utils->v_paths, i));
	ft_printf("total: %d\n", total/2);
	while (y < v_files->len)
	{
		stat((const char *)vec_get(v_files, y), &utils->statbuf);
		print_file_props(utils->statbuf);
 		ft_printf("%s\n", no_path((char *)vec_get(v_files, y)));
		y++;
	}
	if (utils->v_paths.len && i != utils->v_paths.len - 1)
		write(1, "\n", 1);
}

void	print_it(t_ls *utils, t_vec v_files, size_t i, int total)
{
	if (is_bit_set(utils->bit_flags, L))
		print_stat(utils, &v_files, i, total);
	else
		print_files(utils, &v_files, i);
}