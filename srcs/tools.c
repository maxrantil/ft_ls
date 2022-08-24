#include "ft_ls.h"

int	is_bit_set(unsigned int bit_str, unsigned int value)
{
	if (bit_str & value)
		return (1);
	return (0);
}

DIR		*open_path(t_ls *utils, size_t i)
{
	char	path[MAX_PATH];

	ft_strcpy(path, (const char *)vec_get(&utils->v_paths, i));
	utils->dp[i] = opendir(path);
	if (!utils->dp[i])
	{
		ft_printf("ft_ls: cannot access '%s': ", path);
		perror("");
	}
	return (utils->dp[i]);
}

char	*no_path(char *file_with_path)
{
	size_t n;

	n = ft_strlen(file_with_path);
	while (file_with_path[n] != '/' && n > 0)
		n--;
	if (n == 0)
		return (&file_with_path[n]);
	return (&file_with_path[++n]);
}