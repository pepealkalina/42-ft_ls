/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:13:43 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/02/08 16:52:01 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_strlen(const char *string)
{
    int i = 0;
    if (!string)
        return(i);
    while (string[i])
        i++;
    return(i);
}

int dirlen(DIR *dir)
{
    int i = 0;

    while(readdir(dir) != NULL)
        i++;
    return (i);
    closedir(dir);
}

void    ft_swap(void **arr, int i, int j)
{
    void *tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	i = 0;

	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s1[i] > s2[i])
			return (1);
		i++;
	}
	return (0);
}

void    reset_file_array(t_info *ls_info)
{
    int i = 0;

    while (ls_info->files_array[i])
    {
        ls_info->files_array[i] = NULL;
        i++;
    }
}