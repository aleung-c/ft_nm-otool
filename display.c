/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:51:23 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/27 12:51:25 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
#include <stdio.h> //

void	nm_print(t_nm *nm)
{
	t_nm_output		*tmp;
	char			buf[16];

	if (nm->output_list == NULL)
		return ;
	else
	{
		tmp = nm->output_list;
		while (tmp != NULL)
		{
			if (tmp->sym_value != 0x0 
				|| ft_strcmp(tmp->sym_str, "__mh_execute_header") == 0)
			{
				if (tmp->arch_type == 64)
					print_format_hex_address(buf, 16, tmp->sym_value);
				else
					print_format_hex_address(buf, 8, tmp->sym_value);
				//printf(" %x \n", tmp->sym_value);
			}
			else
			{
				if (tmp->arch_type == 64)
					ft_putstr("                ");
				else
					ft_putstr("        ");
			}
			ft_putchar(' ');
			ft_putchar(tmp->sym_type);
			ft_putchar(' ');
			ft_putendl(tmp->sym_str);
			tmp = tmp->next;
		}
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