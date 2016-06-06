/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_otool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 15:39:07 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/06 15:39:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void ot_print_from_list(t_nm *nm_list, int i)
{
	t_nm *tmp;

	if (nm_list == NULL)
		return ;
	tmp = nm_list;
	//if (i > 2 || (i == 2 && tmp->is_ar == 1))
	ft_putchar('\n');
	while (tmp)
	{
		if (i > 2)
		{
			if (!tmp->is_ar && !tmp->is_fat)
			{
				ft_putstr(tmp->str_label);
				ft_putendl(":");
			}
		}
		if (tmp->is_ar)
		{
			//nm_print_from_list(tmp->ar_childs, 0);
		}
		if (tmp->is_ar_member)
		{
			ft_putstr(tmp->ar_name);
			ft_putstr("(");
			ft_putstr(tmp->str_label);
			ft_putstr(")");
			ft_putstr(":\n");
		}
		ot_print(tmp);
		if (tmp->next)
			ft_putchar('\n');
		tmp = tmp->next;
	}
}

void ot_print(t_nm	*nm)
{
	t_ot_output			*tmp;
	unsigned int		sect_size_counter;
	unsigned int		sect_max_size;
	char				buffer[2];
	char				*ptr_to_text;

	if (nm->ot_output_list == NULL)
		return ;
	else
	{
		tmp = nm->ot_output_list;
		printf("%d\n", tmp->sect_size);
		while (tmp)
		{
			sect_size_counter = 0;
			sect_max_size = tmp->sect_size;
			ptr_to_text = tmp->sect_mem;
			sect_size_counter = 0;
			while (sect_size_counter < sect_max_size)
			{
				ft_putendl("hey");
				if (sect_size_counter % 16 == 0)
				{
					if (sect_size_counter != 0)
						ft_putchar('\n');
					print_format_hex_address(buffer, 16, (unsigned long)((void *)tmp->sect_addr + sect_size_counter));
					ft_putstr(" ");
				}
				ft_putnbytes(buffer, 2, *(char *)(ptr_to_text));
				ft_putchar(' ');
				//ft_putnbytes(buffer, 16, *(unsigned long *)(ptr_to_text + sizeof(unsigned long)));
				//ft_putchar('\n');
				ptr_to_text = (char *)ptr_to_text + 1;
				sect_size_counter += (sizeof(char));			
			}
			tmp = tmp->next;
		}
	}
}

void ft_putnbytes(char *buffer, size_t size, unsigned int n)
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