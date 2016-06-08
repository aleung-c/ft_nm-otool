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

/*
** Recursive printing for list and inner lists;
*/

void	ot_print_from_list(t_nm *nm_list, int i)
{
	t_nm *tmp;

	if (nm_list == NULL)
		return ;
	tmp = nm_list;
	while (tmp)
	{
		print_file_name(tmp);
		if (tmp->is_ar)
			ot_print_from_list(tmp->ar_childs, -1);
		if (tmp->is_ar_member)
			print_ar_member_name(tmp);
		if (!tmp->is_err && count_ot_outputs(tmp) != 0)
			ft_putendl("\n(__TEXT,__text) section");
		else if (i != -1 && !tmp->is_ar && (count_ot_outputs(tmp) == 0))
			ft_putendl(" is not an object file");
		ot_print(tmp);
		tmp = tmp->next;
	}
}

void	ot_print(t_nm *nm)
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
		while (tmp)
		{
			sect_size_counter = 0;
			ptr_to_text = tmp->sect_mem;
			while (sect_size_counter < tmp->sect_size)
			{
				print_ot_addr_val(buffer, nm, tmp, sect_size_counter);
				print_section_bytes(buffer, ptr_to_text);
				ptr_to_text = (char *)ptr_to_text + 1;
				sect_size_counter += 1;
			}
			tmp = tmp->next;
		}
		ft_putchar('\n');
	}
}

void	print_file_name(t_nm *tmp)
{
	if (tmp->is_ar)
	{
		ft_putstr("Archive : ");
		ft_putendl(tmp->str_label);
	}
	if (!tmp->is_ar && !tmp->is_ar_member)
	{
		ft_putstr(tmp->str_label);
		ft_putstr(":");
	}
}

void	print_ar_member_name(t_nm *tmp)
{
	ft_putstr(tmp->ar_name);
	ft_putstr("(");
	ft_putstr(tmp->str_label);
	ft_putstr("):");
}

void	print_ot_addr_val(char *buffer, t_nm *nm, t_ot_output *tmp,
						int sect_size_counter)
{
	if (sect_size_counter % 16 == 0)
	{
		if (sect_size_counter != 0)
			ft_putchar('\n');
		if (nm->arch_type == 64)
			print_format_hex_address(buffer, 16, (unsigned long)
				((void *)tmp->sect_addr + sect_size_counter));
		else
			print_format_hex_address(buffer, 8, (unsigned long)
				((void *)tmp->sect_addr + sect_size_counter));
		ft_putstr(" ");
	}
}
