/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:48:37 by preina-g          #+#    #+#             */
/*   Updated: 2022/10/10 13:13:26 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(char const *str, ...);
int	ft_printchar(int c);
int	ft_printstr(char *s);
int	ft_putnbr(long nb);
int	ft_print_ptr(unsigned long long ptr);
int	ft_printu(unsigned int nb);
int	ft_print_hex(unsigned int nbr);
int	ft_printp(unsigned long long ptr);

#endif