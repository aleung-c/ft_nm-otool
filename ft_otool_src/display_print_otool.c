/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_print_otool.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 15:55:52 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/08 15:55:54 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void	ft_putnbytes(char *buffer, size_t size, unsigned int n)
{
	size_t			i;
	size_t			j;
	unsigned		digit;

	i = 0;
	while (i < size)
	{
		digit = n & 0xf;
		buffer[i] = digit < 10 ? digit + '0' : digit - 10 + 'a';
		n >>= 4;
		i++;
	}
	buffer[i + 1] = '\0';
	i -= 1;
	j = 0;
	while (j < size)
	{
		write(1, &(buffer[i]), 1);
		i--;
		j++;
	}
}

void	print_format_hex_address(char *buffer, size_t size, long n)
{
	size_t		i;
	size_t		j;
	unsigned	digit;

	i = 0;
	while (i < size)
	{
		digit = n & 0xf;
		buffer[i] = digit < 10 ? digit + '0' : digit - 10 + 'a';
		n >>= 4;
		i++;
	}
	buffer[i + 1] = '\0';
	j = 0;
	i -= 1;
	while (j < size)
	{
		write(1, &(buffer[i]), 1);
		i--;
		j++;
	}
}

void	print_section_bytes(char *buffer, char *ptr_to_text)
{
	ft_putnbytes(buffer, 2, *(char *)(ptr_to_text));
	ft_putchar(' ');
}
