/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:19:45 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/22 02:19:58 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_slink(struct stat *s_fd_info, char **routes, int i)
{
    if (S_ISLNK(s_fd_info[i].st_mode))
    {
        char fd_target[PATH_MAX];
        ssize_t len = readlink(routes[i], fd_target, sizeof(fd_target) - 1);
        if (len == -1) 
        {
            perror("readlink");
            return;
        }
        fd_target[len] = '\0';
        ft_printf(" -> %s", fd_target);
    }
}

void    print_files_std(struct dirent **files_array, struct stat *s_fd_info, char **routes, t_flags *flags, int count)
{   
    int col_size = get_max_name_len(files_array, count);

    for (int i = 0; i < count; i++)
    {
        if (files_array[i]->d_name[0] == '.' && flags->flag_a != 1)
        continue;
        if (flags->flag_l == 1)
        {
            get_name_group_col(s_fd_info, flags, count);
            print_large_out(&s_fd_info[i], flags);
            ft_printf("%s", files_array[i]->d_name);
            print_slink(s_fd_info, routes, i);
            write(1, "\n", 1);
        }
        else
        {
            print_column(files_array[i]->d_name, col_size);
            write(1, " ", 1);
        }
    }
    if (flags->flag_l != 1)
        write(1, "\n", 1);
}