/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:48:42 by preina-g          #+#    #+#             */
/*   Updated: 2024/02/20 15:41:48 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_printstr("(null)"));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_numlen(long i)
{
	int	j;

	j = 0;
	if (i == -2147483648)
		return (11);
	if (i == 0)
		return (1);
	else if (i < 0)
	{
		j++;
		i = i * -1;
	}
	while (i > 0)
	{
		i = i / 10;
		j++;
	}
	return (j);
}

int	ft_putnbr(long nb)
{
	if (nb == -2147483648)
	{
		ft_putnbr(nb / 10);
		ft_printchar('8');
	}
	else if (nb < 0)
	{
		ft_printchar('-');
		ft_putnbr(-nb);
	}
	else
	{
		if (nb > 9)
			ft_putnbr(nb / 10);
		ft_printchar('0' + (nb % 10));
	}
	return (ft_numlen(nb));
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += ft_printchar('0');
	else if (ptr > 0)
	{
		if (ptr >= 16)
			len += ft_print_ptr(ptr / 16);
		if ((ptr % 16) >= 10)
			len += ft_printchar('W' + (ptr % 16));
		else
			len += ft_printchar('0' + ptr % 16);
	}
	return (len);
}

int	ft_print_hex(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len += ft_printchar('0');
	else if (nbr > 0)
	{
		if (nbr >= 16)
			len += ft_print_hex(nbr / 16);
		if ((nbr % 16) >= 10)
			len += ft_printchar('7' + (nbr % 16));
		else
			len += ft_printchar('0' + nbr % 16);
	}
	return (len);
}
