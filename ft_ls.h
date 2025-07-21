/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:31 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/21 12:20:26 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ft_printf/includes/ft_printf.h"

# define FLAGS "lRart"


/*
    @brief Save info necessary for doing ls

    @param dir_path: path of the directory
    @param dir: pointer to the directory
    @param files_array: array of files in the directory
*/
typedef struct s_info
{
    const char      *dir_path; 
    DIR             *dir;
    struct dirent   **files_array;
}t_info;

typedef struct s_flags
{
    int     flag_l;
    int     flag_R;
    int     flag_r;
    int     flag_t;
    int     flag_a;
    int     name_col;
    int     gr_col;
}t_flags;

/*
    === Utils Functions ===
*/

/*
    @brief Get the len of an array

    @param string: the string to get the len
    @return Return an int with the string len
*/
int     ft_strlen(const char *string);

/*
    @brief Get the len of a dir

    @param ls_info: contains the info of the dir  
    @return Return an int with the amount of files in the dir
*/
int     dirlen(DIR* dir);

/*
    @brief Swap two elements of an array

    @param arr: a pointer to the array
    @param i: position of one element
    @param j: position of the other element
    @return Return an int with the amount of files in the dir
*/
void    ft_swap(void **arr, int i, int j);

/*
    @brief compares two string with n len

    @param s1: string to compare
    @param s2: the other string to compare
    @param n: len of the strings to compare
    @return Return 1 if s1 is greater than s2, -1 if s1 is less than s2, 0 if both strings are equals
*/
int	    ft_strncmp(char *s1, char *s2, unsigned int n);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

/*
    === Files Functions ===
*/

/*
    @brief Sort the files for printing them in alphanumerical order

    @param ls_info: contains the info of the dir 
*/
void    sort_files(struct dirent **files_array, struct stat *s_fd_info, char **routes);

void    sort_files_reverse(struct dirent **files_array, struct stat *s_fd_info, char **routes);

/*
    @brief read the files in a dir an saves them in ls_info->files_array

    @param ls_info: contains the info of the dir 
*/
void    read_files_recursive(char *dir_path);

/*
    @brief Print the files the dir but not print . and ..

    @param ls_info: contains the info of the dir 
*/
void    print_files_std(struct dirent **files_array, struct stat *s_fd_info, char **routes, t_flags *flags, int count);

void    sort_files_time(struct stat *s_fd_info, struct dirent **files_array, char **routes);
void    sort_files_time_reverse(struct stat *s_fd_info, struct dirent **files_array, char **routes);


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void print_large_out(struct stat *s_file_infos,t_flags *col_size);
void ft_putchar(char c);
int	ft_putnbr(long nb);
int ft_intlen(long size);
int get_max_size_len(struct stat *s_fd_info, int len_dir);
int get_max_name_len(struct dirent **files_array, int len_dir);
char	**ft_split(char const *s, char c);

void free_doble(char **pointer);
void ft_not_dir_error(const char *dir);

void get_name_group_col(struct stat *s_file_info, t_flags *col_size, int len);
void print_column(char *str, int max_size_len);


#endif