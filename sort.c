/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:34:40 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/22 00:24:33 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void sort_in_dir(struct dirent **dir_files, struct stat *s_fd_info, char **routes, t_flags *flags)
{
     if (flags->flag_t == 1 && flags->flag_r == 1)
        sort_files_time_reverse(s_fd_info, dir_files, routes);
    else if (flags->flag_t == 1)
        sort_files_time(s_fd_info, dir_files, routes);
    else if (flags->flag_r == 1)
        sort_files_reverse(dir_files, s_fd_info, routes);
    else
        sort_files(dir_files, s_fd_info, routes);
}

void    sort_files(struct dirent **files_array, struct stat *s_fd_info, char **routes)
{
    (void)s_fd_info;
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            if (ft_strncmp(files_array[i]->d_name, \
            files_array[j]->d_name, \
            ft_strlen(files_array[j]->d_name)) == -1)
            {
                ft_swap((void **)files_array, i, j);
                ft_swap((void **)routes, i, j);
                struct stat tmp = s_fd_info[i];
                s_fd_info[i] = s_fd_info[j];
                s_fd_info[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    sort_files_reverse(struct dirent **files_array, struct stat *s_fd_info, char **routes)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            if (ft_strncmp(files_array[i]->d_name, \
            files_array[j]->d_name, \
            ft_strlen(files_array[j]->d_name)) == 1)
            {
                ft_swap((void **)files_array, i, j);
                ft_swap((void **)routes, i, j);
                struct stat tmp = s_fd_info[i];
                s_fd_info[i] = s_fd_info[j];
                s_fd_info[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    sort_files_time(struct stat *s_fd_info, struct dirent **files_array, char **routes)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            if (s_fd_info[i].st_mtime < s_fd_info[j].st_mtime)
            {
                ft_swap((void **)files_array, i, j);
                ft_swap((void **)routes, i, j);
                struct stat tmp = s_fd_info[i];
                s_fd_info[i] = s_fd_info[j];
                s_fd_info[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    sort_files_time_reverse(struct stat *s_fd_info, struct dirent **files_array, char **routes)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            if (s_fd_info[i].st_mtime > s_fd_info[j].st_mtime)
            {
                ft_swap((void **)files_array, i, j);
                ft_swap((void **)routes, i, j);
                struct stat tmp = s_fd_info[i];
                s_fd_info[i] = s_fd_info[j];
                s_fd_info[j] = tmp;
            }
            j++;
        }
        i++;
    }
}


/*Sort in arg array*/

void    sort_files_args(char **files_array)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            if (ft_strncmp(files_array[i], files_array[j], ft_strlen(files_array[j])) == -1)
                ft_swap((void **)files_array, i, j);
            j++;
        }
        i++;
    }
}

void    sort_files_args_reverse(char **files_array)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            if (ft_strncmp(files_array[i], files_array[j], ft_strlen(files_array[j])) == 1)
                ft_swap((void **)files_array, i, j);
            j++;
        }
        i++;
    }
}

time_t get_mtime(const char *filename)
{
    struct stat sb;
    if (stat(filename, &sb) == -1)
        return -1;
    return sb.st_mtime;
}

void    sort_files_args_time(char **files_array)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            time_t time_i = get_mtime(files_array[i]);
            time_t time_j = get_mtime(files_array[j]);

            if (time_i > time_j)
                ft_swap((void **)files_array, i, j);
            j++;
        }
        i++;
    }
}

void    sort_files_args_time_reverse(char **files_array)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
        while (files_array[j])
        {
            time_t time_i = get_mtime(files_array[i]);
            time_t time_j = get_mtime(files_array[j]);

            if (time_i > time_j)
                ft_swap((void **)files_array, i, j);
            j++;
        }
        i++;
    }
}

void sort_in_arg(char **files_array, t_flags *flags)
{
     if (flags->flag_t == 1 && flags->flag_r == 1)
        sort_files_args_time_reverse(files_array);
    else if (flags->flag_t == 1)
        sort_files_args_time(files_array);
    else if (flags->flag_r == 1)
        sort_files_args_reverse(files_array);
    else
        sort_files_args(files_array);
}