/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:33:31 by pepealkalin       #+#    #+#             */
/*   Updated: 2024/11/12 13:13:39 by pepealkalin      ###   ########.fr       */
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

typedef struct s_info
{
    const char      *dir_path; /*save ls dir*/
    DIR             *dir;
    struct dirent   **files_array;
}t_info;

int     ft_strlen(const char *string);
int     dirlen(t_info *ls_info);
void    ft_swap(void **arr, int i, int j);
int	    ft_strncmp(char *s1, char *s2, unsigned int n);

void    sort_files(t_info *ls_info);
void    read_files(t_info *ls_info);
void    print_files_std(t_info *ls_info);


#endif