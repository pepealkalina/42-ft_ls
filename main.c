/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:41 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/22 01:20:58 by pepealkalin      ###   ########.fr       */
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
    {
        perror(dir);
        return (0);
    }
    return (is_dir);
}


void build_path(char *buffer, size_t buffer_size, const char *base, const char *file) 
{
    buffer[0] = '\0'; // Inicializa a cadena vacía

    ft_strlcat(buffer, base, buffer_size - 1);

    // Asegura que haya una '/' si no está ya al final
    if (buffer[strlen(buffer) - 1] != '/')
        ft_strlcat(buffer, "/", buffer_size - strlen(buffer) - 1);

    ft_strlcat(buffer, file, buffer_size - strlen(buffer) - 1);
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
        if (flags->flag_l == 1)
        {
            int total_blocks = 0;
            for(int i = 0; i < len_dir; i++)
                total_blocks += s_fd_info[i].st_blocks;
            
            ft_printf("total ");
            ft_putnbr(total_blocks);
            ft_putchar('\n');
        }
        if (flags->flag_R == 1)
            ft_printf("\n%s:\n", dir_path);
        
        sort_in_dir(dir_files, s_fd_info, routes, flags);

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
        return ;
}

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

void ft_invalid_flag_error(char arg)
{
    write(2, "Error: ", 7);
    write(2, &arg, 1);
    write(2, ": invalid option\n", 18);

    exit(1);
}

char **save_fds(int argc, char const **argv, int start_index)
{
    if (start_index >= argc)
        return (NULL);

    int count = argc - start_index;
    char **args_copy = (char **)malloc((count + 1) * sizeof(char *));
    if (!args_copy)
        return (NULL);

    for (int i = 0; i < count; i++)
    {
        args_copy[i] = ft_strdup(argv[start_index + i]);
        if (!args_copy[i])
        {
            // Si falla malloc, libera lo anterior
            for (int j = 0; j < i; j++)
                free(args_copy[j]);
            free(args_copy);
            return (NULL);
        }
    }
    args_copy[count] = (NULL);
    return (args_copy);
}

int check_file_type(char *path)
{
    struct stat path_stat;

    if (lstat(path, &path_stat) == -1)
        return -1;
    if (S_ISDIR(path_stat.st_mode))
        return 0;
    if (S_ISREG(path_stat.st_mode))
        return 1;
    return -1;
}

void check_files_errors(char **fds)
{
    for (int i = 0; fds[i]; i++)
    {
        struct stat path_stat;
        if (lstat(fds[i], &path_stat) == -1)
            perror(fds[i]);
    }
}

void get_arg_cols(char **fds, t_flags *flag, int len)
{
    struct stat *path_stat = (struct stat *)malloc(len * sizeof(struct stat));;
    for (int i = 0; i < len; i++)
    {
        if (lstat(fds[i], &path_stat[i]) == -1)
        {
            break;
        }
    }
    get_name_group_col(path_stat, flag, len);
    free(path_stat);
}


void parse_flags(int argc, const char **argv, t_flags *flags) 
{   
    int i;
    for (i = 1; i < argc; i++) 
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
                    exit(EXIT_FAILURE);
                }   
            }
        }
        else
            break;
    }
    if (argc == 1)
    {
        read_files(".", flags);
        return;
    }
    int start = i;
    char **fds = save_fds(argc, argv, start);
    if (!fds)
        return;
    //sort args
    sort_in_arg(fds, flags);
    // check if there are erroneous files
    check_files_errors(fds);
    //get for -l
    get_arg_cols(fds, flags, (argc - start));
    
    int col_len = get_max_str_len(fds);
    int found_regfile = 0;
    int len_fds;
    for(i = 0; fds[i]; i++)
    {
        //mira si es un fichero
        if (check_file_type(fds[i]) == 1)
        {
            found_regfile++;
            //mira si la flag l esta para imprimirlo en large
            if (flags->flag_l == 1)
            {
                struct stat path_stat;
                if (lstat(fds[i], &path_stat) == -1)
                    continue;
                print_large_out(&path_stat, flags);
                ft_putchar(' ');
                ft_printf("%s\n", fds[i]);
            }
            else
            {
                print_column(fds[i], col_len);
                ft_putchar(' ');
            }
        }
    }
    len_fds = i;
    if (flags->flag_l != 1)
        ft_putchar('\n');   
    for(i = 0; fds[i]; i++)
    {
        //mira si es un fichero
        if (check_file_type(fds[i]) == 0 && !(argc <= start))
        {
            if (found_regfile == 0)
            {
                ft_printf("%s:\n", fds[i]);
                found_regfile = 1;
            }
            else
                ft_printf("\n%s:\n", fds[i]);
            read_files(fds[i], flags);
        }
        else if(check_file_type(fds[i]) == 0)
            read_files(fds[i], flags);
    }
    ft_free((const char **)fds, len_fds);
}


int main(int argc, char const *argv[])
{
    t_flags flags;

    flags.flag_a = 1;
    flags.flag_l = 1;
    flags.flag_r = 1;
    flags.flag_R = 1;
    flags.flag_t = 1;
    // if there no parametres executes ls in current directory that is .
    if (argc == 1)
        read_files(".", &flags);
    else if (argc > 1)
        parse_flags(argc, argv, &flags);
    return 0;
}
