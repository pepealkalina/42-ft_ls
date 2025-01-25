/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:31 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/01/25 19:15:41 by pepealkalin      ###   ########.fr       */
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
int     dirlen(t_info *ls_info);

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

/*
    === Files Functions ===
*/

/*
    @brief Sort the files for printing them in alphanumerical order

    @param ls_info: contains the info of the dir 
*/
void    sort_files(t_info *ls_info);

/*
    @brief read the files in a dir an saves them in ls_info->files_array

    @param ls_info: contains the info of the dir 
*/
void    read_files(t_info *ls_info);

/*
    @brief Print the files the dir but not print . and ..

    @param ls_info: contains the info of the dir 
*/
void    print_files_std(t_info *ls_info);


#endif