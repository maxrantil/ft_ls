#include "ft_ls.h"

static void	print_permissions(struct stat statbuf)
{
	ft_printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-"); // do i need to fix for 'c' ? it uccurs in /dev
    ft_printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");	
}

static void	print_nbr_hlinks(struct stat statbuf)
{
	ft_printf(" %*i", 2, statbuf.st_nlink);
}

static void	print_owner(struct stat statbuf)
{
	struct passwd *pwd;
	
	pwd = getpwuid(statbuf.st_uid);
	if (pwd == NULL)
    	perror("getpwuid");
	else
    	ft_printf(" %s\t", pwd->pw_name);
}

static void	print_group(struct stat statbuf)
{
	struct group *grp;
	
	grp = getgrgid(statbuf.st_gid);
	if (grp == NULL)
    	perror("getgrgid");
	else
    	ft_printf(" %-s\t", grp->gr_name);
}

static void	print_time(struct stat statbuf)
{
	char	*mtime;
	
	mtime = ft_memalloc(ft_strlen(ctime(&statbuf.st_mtime)));
	ft_strcpy(mtime, ctime(&statbuf.st_mtime));
	ft_printf(" %.12s ", &(mtime[ft_strlen(mtime) - 21]));
	free(mtime);
}

static void	print_size(struct stat statbuf)
{
	ft_printf(" %-i\t", statbuf.st_size);
}

void	print_file_props(struct stat statbuf)
{		
    print_permissions(statbuf);
	print_nbr_hlinks(statbuf);
	print_owner(statbuf);
	print_group(statbuf);
	print_size(statbuf);
	print_time(statbuf);
}