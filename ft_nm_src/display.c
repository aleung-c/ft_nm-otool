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

#include "../includes/ft_nm_otool.h"

void		nm_print(t_nm *nm)
{
	t_nm_output		*tmp;

	if (nm->output_list == NULL)
		return ;
	else
	{
		tmp = nm->output_list;
		while (tmp != NULL)
		{
			print_value_or_not(tmp, nm);
			ft_putchar(' ');
			ft_putchar(tmp->sym_type);
			ft_putchar(' ');
			ft_putstr(tmp->sym_str);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
}

void		print_value_or_not(t_nm_output *tmp, t_nm *nm)
{
	char	*nm_name_cleaned;
	char	*sym_str_cleaned;

	if (nm->is_ar_member)
	{
		nm_name_cleaned = ft_strdup(nm->str_label);
		nm_name_cleaned = clean_name(nm_name_cleaned, 1);
		sym_str_cleaned = ft_strdup(tmp->sym_str);
		sym_str_cleaned = clean_name(sym_str_cleaned, 0);
	}
	if (tmp->sym_value != 0x0
		|| ft_strcmp(tmp->sym_str, "__mh_execute_header") == 0
		|| (nm->is_ar_member
			&& (ft_strcmp(nm_name_cleaned, sym_str_cleaned) == 0))
		|| (tmp->sym_type >= 'a' && tmp->sym_type <= 'z')
		|| (tmp->sym_type == 'T'))
		print_sym_value(tmp, nm->arch_type);
	else
	{
		if (nm->arch_type == 64)
			ft_putstr("                ");
		else
			ft_putstr("        ");
	}
}

/*
** Print nms of argv. if ar, print nms childs recursively.
*/

void		nm_print_from_list(t_nm *nm_list, int i)
{
	t_nm *tmp;

	if (nm_list == NULL)
		return ;
	tmp = nm_list;
	if (i > 2 || (i == 2 && tmp->is_ar == 1))
		ft_putchar('\n');
	while (tmp)
	{
		if (i > 2 && !tmp->is_ar && !tmp->is_fat)
		{
			ft_putstr(tmp->str_label);
			ft_putendl(":");
		}
		if (tmp->is_ar)
			nm_print_from_list(tmp->ar_childs, 0);
		if (tmp->is_ar_member)
			nm_print_ar_label(tmp);
		nm_print(tmp);
		if (tmp->next)
			ft_putchar('\n');
		tmp = tmp->next;
	}
}

void		nm_print_ar_label(t_nm *tmp)
{
	ft_putstr(tmp->ar_name);
	ft_putstr("(");
	ft_putstr(tmp->str_label);
	ft_putstr("):\n");
}
