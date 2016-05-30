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

t_nm	*add_new_nm_file_to_list(t_nm *nm_list, t_nm *new_nm)
{
	t_nm	*tmp;

	if (nm_list == NULL)
	{
		return (new_nm);
	}
	else
	{
		tmp = nm_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_nm;
		return (nm_list);
	}
	return (nm_list);
}

unsigned int swap32(unsigned int x)
{
	return	((x << 24) & 0xff000000 ) |
		((x <<  8) & 0x00ff0000 ) |
		((x >>  8) & 0x0000ff00 ) |
		((x >> 24) & 0x000000ff );
}

void	add_output_to_list(t_nm *nm, t_nm_output *new_output)
{
	t_nm_output			*tmp;

	if (nm->output_list == NULL)
		nm->output_list = new_output;
	else
	{
		/*if (ft_strcmp(new_output->sym_str, nm->output_list->sym_str) < 0)
		{
			new_output->next = nm->output_list;
			nm->output_list = new_output;
			return ;
		}*/			
		tmp = nm->output_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_output;
	}
}