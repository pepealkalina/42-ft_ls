/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:41 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/02/08 17:00:42 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR  *parse_dir(char const *dir)
{
    // check if the first argument is a flag
    DIR *is_dir = opendir(dir);
    if (dir[0] == '-')
        return (0);
    else if (!is_dir)
        return (0);
    return (is_dir);
}
void    read_files(char *dir_path)
{
    DIR *dir = parse_dir(dir_path);

    if (dir)
    {
        int len_dir = dirlen(dir);
        dir = opendir(dir_path);
        struct dirent ** dir_files = (struct dirent **)malloc((len_dir + 1) * sizeof(struct dirent *));
        if (!dir_files)
            return ;
        for (size_t i = 0; i < len_dir; i++)
            dir_files[i] = readdir(dir);
        sort_files(dir_files);
        print_files_std(dir_files);
        free(dir_files);
        closedir(dir);
    }
}

void    sort_files(struct dirent **files_array)
{
    int i = 2;
    while (files_array[i])
    {
        int j = 2;
        while (files_array[j])
        {
            if (ft_strncmp(files_array[i]->d_name, \
            files_array[j]->d_name, \
            ft_strlen(files_array[j]->d_name)) == -1)
                ft_swap((void **)files_array, i, j);
            j++;
        }
        i++;
    }
}

void    print_files_std(struct dirent **files_array)
{
    int i = 0;
    while (files_array[i])
    {
        if (files_array[i]->d_name[0] == '.')
        {
            i++;
            continue;
        }
        write(1, files_array[i]->d_name, ft_strlen(files_array[i]->d_name));
        write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}

//Write the not dir error msg and exits
void ft_not_dir_error(const char *dir)
{
    // Write in stderr Error: <dir>: dir not found
    write(2, "Error: ", 7);
    write(2, dir, ft_strlen(dir));
    write(2, ": dir not found\n", 16);

    exit(1);
}


void    ft_free(t_info *ls_info)
{
    (void)ls_info;
    // free(ls_info->files_array);
}

int main(int argc, char const *argv[])
{
    read_files(".");
    return 0;
}
