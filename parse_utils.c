/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:23:30 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/22 02:27:15 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


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
    else
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