#include "ft_ls.h"
#include <sys/ioctl.h>
#include <termios.h>

static void pr_winsize(int fd)
{
	struct winsize	size;

	if (ioctl(fd, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	ft_printf("%d: rows, %d: colums\n", size.ws_row, size.ws_col);
}

static void	sig_winch(int signo)
{
	ft_printf("SIGWINCH recieved\n");
	pr_winsize(STDIN_FILENO);
}

int	window_size(void)
{
	if (isatty(STDIN_FILENO) == 0)
		exit(1);
	if (signal(SIGWINCH, sig_winch) == SIG_ERR)
		perror("signal");
	pr_winsize(STDIN_FILENO);
	return (1);
}