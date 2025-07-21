/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:13:43 by pepealkalin       #+#    #+#             */
/*   Updated: 2025/07/22 01:25:30 by pepealkalin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_putchar(char c)
{
	write(1, &c, 1);
}

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

int ft_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	i = 0;
	unsigned int j = 0;
	while ((s1[i] || s2[j]) && i < n)
	{
		if (s1[i] == '.' && (s1[i + 1] != '.'))
			i++;
		if (s2[j] == '.' && (s2[j + 1] != '.'))
			j++;
		if (ft_tolower(s1[i]) < ft_tolower(s2[j]))
			return (-1);
		if (ft_tolower(s1[i]) > ft_tolower(s2[j]))
			return (1);
		i++;
		j++;
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*s;
	size_t	len_dst;
	size_t	res;
	size_t	len_src;
	size_t	i;

	s = (char *)src;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(s);
	res = 0;
	i = 0;
	if (size > len_dst)
		res = len_src + len_dst;
	else
		res = len_src + size;
	while (s[i] && (len_dst + 1) < size)
	{
		dst[len_dst] = s[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = '\0';
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (dstsize != 0)
	{
		len = ft_strlen(src);
		i = 0;
		while (i < len && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	else
		len = ft_strlen(src);
	return (len);
}

int ft_intlen(long size)
{
	int i = 0;

	while (size)
	{
		i++;
		size = size/10;
	}
	return (i);
}

int get_max_size_len(struct stat *s_fd_info, int len_dir)
{
	int max = 0;
	int i = 0;
	while (i < len_dir)
	{
		if (max < ft_intlen(s_fd_info[i].st_size))
			max = ft_intlen(s_fd_info[i].st_size);
		i++;
	}
	return (max);
}

static size_t	ft_words_count(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (s[i] == '\0')
		return (0);
	if (s[i] != c)
	{
		i++;
		words++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			words++;
		}
		i++;
	}
	return (words);
}

static size_t	ft_wordlen(const char *str, char c, int i)
{
	int	len;

	len = 0;
	while (str[i] != c && str[i])
	{
		i++;
		len++;
	}
	return (len);
}

int get_max_name_len(struct dirent **files_array, int len_dir)
{
	int max = 0;
	int i = 0;
	while (i < len_dir)
	{
		if (max < ft_strlen(files_array[i]->d_name))
			max = ft_strlen(files_array[i]->d_name);
		i++;
	}
	return (max);
}

int get_max_str_len(char **files_array)
{
	int max = 0;
	int i = 0;
	while (files_array[i])
	{
		if (max < ft_strlen(files_array[i]))
			max = ft_strlen(files_array[i]);
		i++;
	}
	return (max);
}

char	*ft_strdup(const char *s)
{
	char	*array;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s);
	array = (char *)malloc(sizeof(char) * (size + 1));
	if (array == NULL)
		return (NULL);
	while (i < size + 1)
	{
		array[i] = s[i];
		i++;
	}
	return (array);
}

char	**ft_free(const char **str, size_t i)
{
	while ((int)i < 0)
	{
		i--;
		free((void *)str[i]);
	}
	free (str);
	return (NULL);
}

static char	**ft_make_split(char **str, const char *s, char c, size_t l)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		str[j] = (char *)malloc(sizeof(char) * (ft_wordlen(s, c, i) + 1));
		if (!str[j])
			return (ft_free((const char **)str, j));
		while (s[i] && s[i] != c)
			str[j][k++] = s[i++];
		str[j][k] = '\0';
		j++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**separated_str;

	if (!s)
		return (NULL);
	words = ft_words_count(s, c);
	separated_str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!separated_str)
	{
		free(separated_str);
		return (NULL);
	}
	return (ft_make_split(separated_str, s, c, words));
}