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


// if archive, print "Archive : lifbt.a"
void ot_print_from_list(t_nm *nm_list, int i)
{
	t_nm *tmp;

	if (i)
	{}
	if (nm_list == NULL)
		return ;
	tmp = nm_list;
	//if (i > 2 || (i == 2 && tmp->is_ar == 1))
	//ft_putchar('\n');
	while (tmp)
	{
		// print file name or archive name;
		if (!tmp->is_ar && !tmp->is_ar_member)
		{
			ft_putstr(tmp->str_label);
			ft_putendl(":");
		}
		if (tmp->is_ar)
		{
			ot_print_from_list(tmp->ar_childs, 0);
		}
		if (tmp->is_ar_member)
		{
			ft_putstr(tmp->ar_name);
			ft_putstr("(");
			ft_putstr(tmp->str_label);
			ft_putstr(")");
			ft_putstr(":\n");
		}
		ft_putendl("(__TEXT,__text) section");
		ot_print(tmp);
		//if (tmp->next)
			ft_putchar('\n');
		tmp = tmp->next;
	}
}

void ot_print(t_nm	*nm)
{
	t_ot_output			*tmp;
	unsigned int		sect_size_counter;
	char				buffer[16];
	char				*ptr_to_text;

	if (nm->ot_output_list == NULL)
		return ;
	else
	{
		tmp = nm->ot_output_list;
		//printf("%d\n", tmp->sect_size);
		while (tmp)
		{
			sect_size_counter = 0;
			ptr_to_text = tmp->sect_mem;
			sect_size_counter = 0;
			while (sect_size_counter < tmp->sect_size)
			{
				/*ft_putendl("hey ");
				ft_putnbr(sect_size_counter);
				ft_putchar('\n');
				ft_putnbr(tmp->sect_size);*/
				if (sect_size_counter % 16 == 0)
				{
					if (sect_size_counter != 0)
						ft_putchar('\n');
					if (nm->arch_type == 64)
						print_format_hex_address(buffer, 16, (unsigned long)((void *)tmp->sect_addr + sect_size_counter));
					else
						print_format_hex_address(buffer, 8, (unsigned long)((void *)tmp->sect_addr + sect_size_counter));
					ft_putstr(" ");
				}
				ft_putnbytes(buffer, 2, *(char *)(ptr_to_text));
				ft_putchar(' ');
				ptr_to_text = (char *)ptr_to_text + 1;
				sect_size_counter += 1;
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