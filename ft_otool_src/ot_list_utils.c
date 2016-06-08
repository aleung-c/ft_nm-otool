/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:28:35 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/06 17:28:36 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void	add_ot_output_to_list(t_nm *nm, t_ot_output *new_output)
{
	t_ot_output			*tmp;

	if (nm->ot_output_list == NULL)
		nm->ot_output_list = new_output;
	else
	{
		tmp = nm->ot_output_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_output;
	}
}
