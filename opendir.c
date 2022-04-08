#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_ls(struct dirent *d, DIR *dir)
{
	while ((d = readdir(dir)) != NULL)
	{
		if (d->d_name[0] == '.')
			continue;
		printf("%s ", d->d_name);
	}
	printf("\n");
}

int main(int argc, const char **argv)
{
	struct dirent *d;
	DIR *dir;

	dir = opendir(".");
	if (!dir)
	{
		perror("error, cant read the directory");
		exit(EXIT_FAILURE);
	}
	if (argc > 1)
	{
		if (argv[1][0] == '-')
		{
			if (argv[1][1] == 'a')
			{
				while ((d = readdir(dir)) != NULL)
				{
					if (d->d_name[0] == '.')
						continue;
					printf("%s\n", d->d_name);
				}
				printf("\n");
			}
			if (argv[1][1] == 'l')
			{
				while ((d = readdir(dir)) != NULL)
				{
					printf("%s\n", d->d_name);
				}
				printf("\n");
			}
		}
	}
	else
	{
		while ((d = readdir(dir)) != NULL)
		{
			if (d->d_name[0] == '.')
				continue;
			printf("%s ", d->d_name);
		}
		printf("\n");
	}
	closedir(dir);
}
