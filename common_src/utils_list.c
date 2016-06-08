/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:32:38 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/08 16:32:42 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

t_nm		*add_new_nm_file_to_list(t_nm *nm_list, t_nm *new_nm)
{
	t_nm	*tmp;

	if (nm_list == NULL)
		return (new_nm);
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

void		add_output_to_list(t_nm *nm, t_nm_output *new_output)
{
	t_nm_output			*tmp;

	if (nm->output_list == NULL)
		nm->output_list = new_output;
	else
	{
		if (ft_strcmp(new_output->sym_str, nm->output_list->sym_str) < 0)
		{
			new_output->next = nm->output_list;
			nm->output_list = new_output;
			return ;
		}
		tmp = nm->output_list;
		while (tmp->next && ft_strcmp(new_output->sym_str,
				tmp->next->sym_str) >= 0)
			tmp = tmp->next;
		if (tmp->next)
			new_output->next = tmp->next;
		else
			new_output->next = NULL;
		tmp->next = new_output;
	}
}

int			count_nm_list_members(t_nm *nm_list)
{
	int		i;
	t_nm	*tmp;

	i = 0;
	tmp = nm_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int			count_nm_outputs(t_nm *nm)
{
	int				i;
	t_nm_output		*tmp;

	i = 0;
	tmp = nm->output_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int			count_ot_outputs(t_nm *nm)
{
	int				i;
	t_ot_output		*tmp;

	i = 0;
	tmp = nm->ot_output_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
