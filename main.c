/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:41 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/21 04:19:26 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR *parse_dir(char const *dir)
{
    // check if the first argument is a flag
    DIR *is_dir = opendir(dir);
    if (!dir)
        return (0);
    else if (!is_dir)
        return (0);
    return (is_dir);
}


void build_path(char *buffer, size_t buffer_size, const char *base, const char *file) 
{
    buffer[0] = '\0'; // Inicializa a cadena vacía

    strncat(buffer, base, buffer_size - 1);

    // Asegura que haya una '/' si no está ya al final
    if (buffer[strlen(buffer) - 1] != '/')
        strncat(buffer, "/", buffer_size - strlen(buffer) - 1);

    strncat(buffer, file, buffer_size - strlen(buffer) - 1);
}

void    read_files(char *dir_path, t_flags *flags)
{
    DIR *dir = parse_dir(dir_path);

    if (dir)
    {
        int len_dir = dirlen(dir);
        closedir(dir);
        dir = opendir(dir_path);
        struct dirent ** dir_files = (struct dirent **)malloc((len_dir + 1) * sizeof(struct dirent *));
        if (!dir_files)
            return ;
        struct stat *s_fd_info = (struct stat *)malloc((len_dir + 1) * sizeof(struct stat));
        if (!s_fd_info)
        return ;
        char **routes = (char **)malloc((len_dir + 1) * sizeof(char *));
        if (!routes)
            return ;
        int j = 0;
        struct dirent *file;
        while ((file = readdir(dir)) && j < len_dir)
        {
            if ((!ft_strncmp(file->d_name, ".", 1) 
            || !ft_strncmp(file->d_name, "..", 2)
            || file->d_name[0] == '.') && flags->flag_a != 1)
                continue;
            dir_files[j] = file;
            
            routes[j] = (char *)malloc(256 * sizeof(char));
            if (!routes[j])
            {
                for (int k = 0; k < j; k++)
                    free(routes[k]);
                free(routes);
                free(dir_files);
                free(s_fd_info);
                return ;
            }
            
            routes[j][0] = '\0';
            
            build_path(routes[j], PATH_MAX, dir_path, dir_files[j]->d_name);

            if (lstat(routes[j], &s_fd_info[j]) < 0)
            {
                free(routes[j]);
                break;
            }
            j++;
        }
        dir_files[j] = NULL;
        routes[j] = NULL;
        if (flags->flag_R == 1)
            ft_printf("\n%s:\n", dir_path);
        
        if (flags->flag_t == 1 && flags->flag_r == 1)
            sort_files_time_reverse(s_fd_info, dir_files);
        else if (flags->flag_t == 1)
            sort_files_time(s_fd_info, dir_files);
        else if (flags->flag_r == 1)
            sort_files_reverse(dir_files);
        else
            sort_files(dir_files);
        
        print_files_std(dir_files, s_fd_info, routes, flags, j);

        if (flags->flag_R == 1)
            for (int i = 0; i < j; i++)
            {
                if (!dir_files[i] || !routes[i])
                    continue;

                if ((!ft_strncmp(dir_files[i]->d_name, ".", 1)) 
                    || !ft_strncmp(dir_files[i]->d_name, "..", 2))
                    continue ;
                
                if (S_ISDIR(s_fd_info[i].st_mode))
                    read_files(routes[i], flags);
            }
        
        for (int k = 0; k < j; k++)
            free(routes[k]);
        
        free(routes);
        free(dir_files);
        free(s_fd_info);
    
        closedir(dir);
    }
    else
    {
        ft_not_dir_error((const char *)dir_path);
        return ;
    }
}



void    sort_files(struct dirent **files_array)
{
    int i = 0;
    while (files_array[i])
    {
        int j = 0;
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

void    sort_files_reverse(struct dirent **files_array)
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
                ft_swap((void **)files_array, i, j);
            j++;
        }
        i++;
    }
}

void    sort_files_time(struct stat *s_fd_info, struct dirent **files_array)
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
                struct stat tmp = s_fd_info[i];
                s_fd_info[i] = s_fd_info[j];
                s_fd_info[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    sort_files_time_reverse(struct stat *s_fd_info, struct dirent **files_array)
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
                struct stat tmp = s_fd_info[i];
                s_fd_info[i] = s_fd_info[j];
                s_fd_info[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    print_files_std(struct dirent **files_array, struct stat *s_fd_info, char **routes, t_flags *flags, int count)
{   
    for (int i = 0; i < count; i++)
    {
        if (files_array[i]->d_name[0] == '.' && flags->flag_a != 1)
        {
            i++;
            continue;
        }
        if (flags->flag_l == 1)
        {
            print_large_out(&s_fd_info[i]);
            ft_printf("%s", files_array[i]->d_name);
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
            write(1, "\n", 1);
        }
        else
        {
            write(1, files_array[i]->d_name, ft_strlen(files_array[i]->d_name));
            write(1, " ", 1);
        }
    }
    if (flags->flag_l != 1)
        write(1, "\n", 1);
}

void ft_invalid_flag_error(char arg)
{
    write(2, "Error: ", 7);
    write(2, &arg, 1);
    write(2, ": invalid option\n", 18);

    exit(1);
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


void parse_flags(int argc, const char **argv, t_flags *flags) 
{
    for (int i = 1; i < argc; i++) 
    {
        // Solo procesar argumentos que empiezan con '-'
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) 
            {
                if (argv[i][j] == 'l')
                    flags->flag_l = 1;
                else if (argv[i][j] == 'a')
                    flags->flag_a = 1;
                else if (argv[i][j] == 'r')
                    flags->flag_r = 1;
                else if (argv[i][j] == 't')
                    flags->flag_t = 1;
                else if (argv[i][j] == 'R')
                    flags->flag_R = 1;
                else
                {
                    ft_invalid_flag_error(argv[i][j]);
                    return;
                }   
            }
        }
        else
        {
            read_files((char *)argv[i], flags);
        }
    }
    if (argv[argc - 1][0] == '-')
        read_files(".", flags);
}


int main(int argc, char const *argv[])
{
    t_flags flags;

    // if there no parametres executes ls in current directory that is .
    if (argc == 1)
        read_files(".", &flags);
    else if (argc > 1)
    {
        parse_flags(argc, argv, &flags);
    }
    return 0;
}
