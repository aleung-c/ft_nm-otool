/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:01:25 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/30 17:01:29 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void nm_sort(t_nm *nm)
{
	// Tri à bulle.
	t_nm_output		*tmp;
	t_nm_output		*stock;

	if (nm->output_list == NULL)
		return ;
	tmp = nm->output_list;
	while (tmp)
	{
		if (tmp->next
			&& ft_strcmp(tmp->sym_str, tmp->next->sym_str) > 0)
		{
			stock = tmp->next;
			tmp->next = tmp->next->next;
			stock->next = nm->output_list;
			nm->output_list = stock;
			tmp = nm->output_list;
		}
		else
			tmp = tmp->next;
	}
}
