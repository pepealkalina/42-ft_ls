/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:41 by pepealkalin       #+#    #+#             */
/*   Updated: 2024/11/12 13:13:38 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int  parse_dir(char const *dir, t_info *ls_info)
{
    // check if the first argument is a flag
    ls_info->dir = opendir(dir);
    if (dir[0] == '-')
        return (0);
    else if (!ls_info->dir)
        return (0);
    
    ls_info->dir_path = dir;
    return (1);
}
void    read_files(t_info *ls_info)
{
    int len_dir = dirlen(ls_info);
    ls_info->dir = opendir(ls_info->dir_path);
    int i = 0;

    ls_info->files_array = (struct dirent **)malloc(len_dir * sizeof(struct dirent *));
    if (!ls_info->files_array)
        return ;
    while (i < len_dir)
    {
        ls_info->files_array[i] = readdir(ls_info->dir);
        i++;
    }
    closedir(ls_info->dir);
}

void    sort_files(t_info *ls_info)
{
    int i = 2;
    while (ls_info->files_array[i])
    {
        int j = 2;
        while (ls_info->files_array[j])
        {
            if (ft_strncmp(ls_info->files_array[i]->d_name, ls_info->files_array[j]->d_name, ft_strlen(ls_info->files_array[j]->d_name)) == -1)
                ft_swap((void **)ls_info->files_array, i, j);
            j++;
        }
        i++;
    }
    
}

void    print_files_std(t_info *ls_info)
{
    int i = 2;
    while (ls_info->files_array[i])
    {
        if (ls_info->files_array[i]->d_name[0] == '.')
        {
            i++;
            continue;
        }
        write(1, ls_info->files_array[i]->d_name, ft_strlen(ls_info->files_array[i]->d_name));
        write(1, "\n", 1);
        i++;
    }
}


void    ft_free(t_info *ls_info)
{
    (void)ls_info;
    // free(ls_info->files_array);
}

int main(int argc, char const *argv[])
{
    t_info ls_info;

    if (argc == 1)
    {
        parse_dir(".", &ls_info);
        read_files(&ls_info);
        print_files_std(&ls_info);
    }
    else if (argc > 1)
    {
        int is_dir = parse_dir(argv[1], &ls_info);
        if (argc == 2 && is_dir)

    }
    ft_free(&ls_info);
    return 0;
}
