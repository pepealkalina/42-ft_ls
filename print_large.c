/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:02:47 by preina-g          #+#    #+#             */
/*   Updated: 2025/07/21 12:55:10 by preina-g         ###   ########.fr       */
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
	int i = 0;
	if (size == 0)
		i = 1;

	if (ft_intlen(size) < max_size_len)
	{
		while (i++ < (max_size_len - ft_intlen(size)))
			ft_putchar(' ');
	}
	ft_putnbr(size);
}

void print_column(char *str, int max_size_len)
{
	int i = 0;
	if (!str)
		return;
	
	write(1, str, ft_strlen(str));
	if (ft_strlen(str) < max_size_len)
	{
		while (i++ < (max_size_len - ft_strlen(str)))
			ft_putchar(' ');
	}
}

void free_doble(char **pointer)
{
	int i = 0;

	if (!pointer)
        return;

	while(pointer[i++])
		if (pointer[i])
			free(pointer[i]);
	free(pointer);
}

int ft_atoi_simple(const char *str)
{
    int i = 0;
    int res = 0;

    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

void free_splited_hour(char **splited_hour)
{
	free(splited_hour[0]);
	free(splited_hour[1]);
	free(splited_hour[2]);
	free(splited_hour);
}

void free_splited_str(char **splited_str)
{
	free(splited_str[4]);
	free(splited_str[3]);
	free(splited_str[2]);
	free(splited_str[1]);
	free(splited_str[0]);
	free(splited_str);
}

void print_time(char *mtime)
{
	char **splited_str = ft_split(mtime, ' ');

	ft_printf("%s ", splited_str[1]);
	if (ft_strlen(splited_str[2]) == 1)
		ft_printf(" %s ", splited_str[2]);
	else
		ft_printf("%s ", splited_str[2]);


	if (ft_atoi_simple(splited_str[4]) == 2025)
	{
		char **splited_hour = ft_split(splited_str[3], ':');
		ft_printf("%s:", splited_hour[0]);
		ft_printf("%s ", splited_hour[1]);
		free_splited_hour(splited_hour);
	}
	else
	{
		splited_str[4][ft_strlen(splited_str[4]) - 1] = '\0';
		ft_printf("%s  ", splited_str[4]);
	}
	free_splited_str(splited_str);
}


int get_major(dev_t dev) {
    return (int)((dev >> 8) & 0xFFF);
}

// Versión funcional de minor()
int get_minor(dev_t dev) {
    return (int)((dev & 0xFF) | ((dev >> 12) & 0xFFF00));
}

void get_name_group_col(struct stat *s_file_info, t_flags *col_size, int len)
{
	int s_passwd;
	int s_group;
	col_size->name_col = 0;
	col_size->gr_col = 0;

	for (int i = 0; i < len; i++)
	{
		s_passwd = ft_strlen(getpwuid(s_file_info[i].st_uid)->pw_name);
		s_group = ft_strlen(getgrgid(s_file_info[i].st_gid)->gr_name);

		if (col_size->name_col < s_passwd)
			col_size->name_col = s_passwd;
		if (col_size->gr_col < s_group)
			col_size->gr_col = s_group;
	}
	
}

void print_large_out(struct stat *s_file_info, t_flags *col_size)
{
	struct passwd *s_passwd = getpwuid(s_file_info->st_uid);
	struct group *s_group = getgrgid(s_file_info->st_gid);


    print_mode(s_file_info->st_mode);
	ft_putchar(' ');
	print_size(s_file_info->st_nlink, 2);
	ft_putchar(' ');
	print_column(s_passwd->pw_name, col_size->name_col);
	ft_putchar(' ');
	print_column(s_group->gr_name, col_size->gr_col);
	if (S_ISCHR(s_file_info->st_mode) || S_ISBLK(s_file_info->st_mode))
	{
		print_size(get_major(s_file_info->st_rdev), 3);
		write(1, ", ", 2);
		print_size(get_minor(s_file_info->st_rdev), 3);
	}
	else
		print_size(s_file_info->st_size, 8);
	ft_putchar(' ');
	print_time(ctime(&s_file_info->st_mtime));
}