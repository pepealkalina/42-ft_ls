/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:41 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/22 02:27:07 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
    int start = i;
    char **fds = save_fds(argc, argv, start);
    if (!fds)
    {
        read_files(".", flags);
        return;
    }
    //sort args
    sort_in_arg(fds, flags);
    // check if there are erroneous files
    check_files_errors(fds);
    //get for -l
    get_arg_cols(fds, flags, (argc - start));
    
    int col_len = get_max_str_len(fds);
    int found_regfile = 0;
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
                ft_printf("%s", fds[i]);
                print_slink(&path_stat, fds, i);
                ft_putchar('\n');
            }
            else
            {
                print_column(fds[i], col_len);
                ft_putchar(' ');
            }
        }
    }
    if (flags->flag_l != 1 && found_regfile >= 1)
        ft_putchar('\n');   
    for(i = 0; fds[i]; i++)
    {
        //mira si es un fichero
        if (check_file_type(fds[i]) == 0 && !(argc <= start))
        {
            if (found_regfile == 0 && fds[i+1] != NULL)
            {
                ft_printf("%s:\n", fds[i]);
                found_regfile = 1;
            }
            else if (found_regfile >= 1)
                ft_printf("\n%s:\n", fds[i]);
            read_files(fds[i], flags);
        }
        else if(check_file_type(fds[i]) == 0)
            read_files(fds[i], flags);
    }
    free_doble(fds);
}


int main(int argc, char const *argv[])
{
    t_flags flags;
    // if there no parametres executes ls in current directory that is .
    if (argc == 1)
        read_files(".", &flags);
    else if (argc > 1)
        parse_flags(argc, argv, &flags);
    return 0;
}
