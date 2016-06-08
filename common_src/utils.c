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

#include "../includes/ft_nm_otool.h"

void			to_hex(char *buffer, size_t size, unsigned n)
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

unsigned int	swap32(unsigned int x)
{
	return	((x << 24) & 0xff000000 ) |
		((x <<  8) & 0x00ff0000) |
		((x >>  8) & 0x0000ff00) |
		((x >> 24) & 0x000000ff);
}

int				str_to_int(char *val)
{
	int i;
	int ret;
	int multiple;

	i = 0;
	ret = 0;
	multiple = 1;
	while (val[i] && val[i] != 96 && val[i] != 10 && val[i] != 32)
		i++;
	i--;
	while (i != -1)
	{
		ret = (val[i] - '0') * multiple + ret;
		multiple *= 10;
		i--;
	}
	return (ret);
}

void			print_error(char **argv, int i, int error_type)
{
	ft_putstr(argv[i]);
	if (error_type == 1)
		ft_putendl(": Is a directory or invalid file.");
	else if (error_type == 2)
		ft_putendl(": No such file or directory.");
}
