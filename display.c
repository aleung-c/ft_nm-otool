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

void	nm_print(t_nm *nm)
{
	t_nm_output		*tmp;

	if (nm->output_list == NULL)
	{
		return ;
	}
	else
	{
		tmp = nm->output_list;
		while (tmp != NULL)
		{
			if (tmp->sym_value != 0x0 
				|| ft_strcmp(tmp->sym_str, "__mh_execute_header") == 0)
				print_format_hex_address(tmp->sym_output);
			else
				ft_putstr("                ");
			ft_putchar(' ');
			ft_putchar(tmp->sym_type);
			ft_putchar(' ');
			ft_putendl(tmp->sym_str);
			tmp = tmp->next;
		}
	}

}