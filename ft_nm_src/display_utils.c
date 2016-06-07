/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 17:58:48 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/07 17:58:50 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void		print_sym_value(t_nm_output *tmp, int arch_type)
{
	char			buf[16];

	if (arch_type == 64)
		print_format_hex_address(buf, 16, tmp->sym_value);
	else
		print_format_hex_address(buf, 8, tmp->sym_value);
}

void		print_format_hex_address(char *buffer, size_t size, long n)
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

char		*clean_name(char *raw_name, int ext)
{
	int		i;

	i = 0;
	if (ext == 1)
	{
		while (raw_name[i] && raw_name[i] != '.')
			i++;
		raw_name[i] = '\0';
		return (raw_name);
	}
	else
	{
		while (raw_name[i] && raw_name[i] == '_')
			i++;
		return (&(raw_name[i]));
	}
}
