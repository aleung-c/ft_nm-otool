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
	

	if (nm->output_list == NULL)
		return ;
	else
	{
		tmp = nm->output_list;
		while (tmp != NULL)
		{
			// TODO : print 0x0 addr if is the same as the .o
			print_value_or_not(tmp, nm);
			/*if (tmp->sym_value != 0x0 
				|| ft_strcmp(tmp->sym_str, "__mh_execute_header") == 0)
			{
				if (tmp->arch_type == 64)
					print_format_hex_address(buf, 16, tmp->sym_value);
				else
					print_format_hex_address(buf, 8, tmp->sym_value);
			}
			else
			{
				if (tmp->arch_type == 64)
					ft_putstr("                ");
				else
					ft_putstr("        ");
			}*/
			ft_putchar(' ');
			ft_putchar(tmp->sym_type);
			ft_putchar(' ');
			ft_putstr(tmp->sym_str);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
}

void	print_value_or_not(t_nm_output *tmp, t_nm *nm)
{
	
	char	*nm_name_cleaned;
	char	*sym_str_cleaned;

	if (nm->is_ar_member)
	{
		nm_name_cleaned = ft_strdup(nm->str_label);
		nm_name_cleaned = clean_name(nm_name_cleaned, 1);
		sym_str_cleaned = ft_strdup(tmp->sym_str);
		sym_str_cleaned = clean_name(sym_str_cleaned, 0);
		//ft_putendl(nm_name_cleaned);
		//ft_putendl(sym_str_cleaned);
	}

	if (tmp->sym_value != 0x0 
		|| ft_strcmp(tmp->sym_str, "__mh_execute_header") == 0
		|| (nm->is_ar_member 
			&& (ft_strcmp(nm_name_cleaned, sym_str_cleaned) == 0))
		|| (tmp->sym_type >= 'a' && tmp->sym_type <= 'z')
		|| (nm->is_ar_member && tmp->sym_type == 'T'))
		print_sym_value(tmp);
	else
	{
		if (tmp->arch_type == 64)
			ft_putstr("                ");
		else
			ft_putstr("        ");
	}
}

void		print_sym_value(t_nm_output *tmp)
{
	char			buf[16];

	if (tmp->arch_type == 64)
			print_format_hex_address(buf, 16, tmp->sym_value);
		else
			print_format_hex_address(buf, 8, tmp->sym_value);
}

char		*clean_name(char *raw_name, int ext)
{
	int		i;

	i = 0;
	if (ext == 1)
	{
		while(raw_name[i] && raw_name[i] != '.')
			i++;
		raw_name[i] = '\0';
		return (raw_name);
	}
	else
	{
		while(raw_name[i] && raw_name[i] == '_')
			i++;
		return (&(raw_name[i]));
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

/*
** Print nms of argv. if ar, print nms childs recursively.
*/
void		nm_print_from_list(t_nm *nm_list, int i)
{
	t_nm *tmp;

	tmp = nm_list;
	if (i > 2 || (i == 2 && tmp->is_ar == 1))
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
			nm_print_from_list(tmp->ar_childs, 0);
		}
		if (tmp->is_ar_member)
		{
			ft_putstr(tmp->ar_name);
			ft_putstr("(");
			ft_putstr(tmp->str_label);
			ft_putstr(")");
			ft_putstr(":\n");
		}
		nm_print(tmp);
		if (tmp->next)
			ft_putchar('\n');
		tmp = tmp->next;
	}
}
