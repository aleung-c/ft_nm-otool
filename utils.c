/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:46:30 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/26 17:46:34 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	to_hex(char *buffer, size_t size, unsigned n)
{
	size_t		i;
	size_t		j;
	char		c;
	unsigned	digit;

	i = 0;
	while (i < size)
	{
		digit = n & 0xf;
		buffer[i] = digit < 10 ? digit + '0' : digit - 10 + 'a';
		n >>= 4;
		if (n == 0)
			break ;
		i++;
	}
	buffer[i + 1] = 0;
	j = 0;
	while (j < i / 2)
	{
		c = buffer[j];
		buffer[j] = buffer[i - j];
		buffer[i - j] = c;
		++j;
	}
}

void print_format_hex_address(char *output)
{
	int		output_length;
	int		i;
	int		y;

	i = 0;
	y = 0;
	output_length = strlen(output);
	while (y < 16)
	{
		if (y >= (16 - output_length) && output[i]) 
		{
			ft_putchar(output[i]);
			i++;
		}
		else if (y == 7)
		{
			ft_putchar('1');
		}
		else
		{
			ft_putchar('0');
		}
		y++;
	}
}