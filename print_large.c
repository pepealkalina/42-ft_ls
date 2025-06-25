/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:02:47 by preina-g          #+#    #+#             */
/*   Updated: 2025/06/24 23:03:30 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
void print_mode(mode_t st_mode)
{
    char	c;

	c = '-';
	c = (S_ISDIR(st_mode)) ? 'd' : c;
	c = (S_ISCHR(st_mode)) ? 'c' : c;
	c = (S_ISBLK(st_mode)) ? 'b' : c;
	c = (S_ISFIFO(st_mode)) ? 'p' : c;
	c = (S_ISLNK(st_mode)) ? 'l' : c;
	c = (S_ISSOCK(st_mode)) ? 's' : c;
	ft_putchar(c);
	ft_putchar((st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((st_mode & S_IXOTH) ? 'x' : '-');
}
// -l

void print_size(long size, int max_size_len)
{
	if (ft_intlen(size) < max_size_len)
	{
		int i = 0;
		while (i++ < (max_size_len - ft_intlen(size)))
			ft_putchar(' ');
	}
	ft_putnbr(size);
}

void free_doble(void **pointer)
{
	int i = 0;

	while(pointer[i++])
		free(pointer[i]);
	
	free(pointer);
}

void print_time(char *time)
{
	char **splited_str = ft_split(time, ' ');

	ft_printf("%s ", splited_str[1]);
	ft_printf("%s ", splited_str[2]);

	char **splited_hour = ft_split(splited_str[3], ':');
	ft_printf("%s:%s ", splited_hour[0], splited_hour[1]);

	// char **splited_date = ft_split(splited_str[4], '\n');
	// ft_printf("%s ", splited_date[0]);

	free_doble((void **)splited_hour);
	free_doble((void **)splited_str);
	// free_doble((void **)splited_date);
}


void print_large_out(struct stat *s_file_info, int max_size_len)
{
	struct passwd *s_passwd = getpwuid(s_file_info->st_uid);
	struct group *s_group = getgrgid(s_file_info->st_gid);


    print_mode(s_file_info->st_mode);
	ft_putchar(' ');
	ft_putnbr(s_file_info->st_nlink);
	ft_printf(" %s %s ", s_passwd->pw_name, s_group->gr_name);
	print_size(s_file_info->st_size, max_size_len);
	ft_putchar(' ');
	print_time(ctime(&s_file_info->st_mtime));
}