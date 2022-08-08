#include "ft_ls.h"

size_t	window_size(void)
{
	struct winsize	size;
	int	fd;

	fd = STDIN_FILENO;
	if (ioctl(fd, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	//ft_printf("%d: rows, %d: colums\n", size.ws_row, size.ws_col);
	return (size.ws_col);
}