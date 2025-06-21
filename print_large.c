/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:02:47 by preina-g          #+#    #+#             */
/*   Updated: 2025/06/21 12:48:13 by preina-g         ###   ########.fr       */
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
void print_large_out(struct stat *s_file_info)
{
	struct passwd *s_passwd = getpwuid(s_file_info->st_uid);
	struct group *s_group = getgrgid(s_file_info->st_gid);

    print_mode(s_file_info->st_mode);
	ft_printf(" %s %s %i\t", s_passwd->pw_name, s_group->gr_name, s_file_info->st_size);

}