#include "ft_ls.h"
#include <sys/ioctl.h>

int	window_size(void)
{
	struct winsize	size;
	int	fd;

	fd = STDIN_FILENO;
	if (ioctl(fd, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	ft_printf("%d: rows, %d: colums\n", size.ws_row, size.ws_col);
	return (1);
}