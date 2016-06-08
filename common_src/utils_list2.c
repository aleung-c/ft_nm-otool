/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:34:25 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/08 16:34:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void		free_unused_child(t_nm *ar_child)
{
		free(ar_child->str_label);
		free(ar_child);
}


int 		check_is_nm_doublon(t_nm *new_nm, t_nm *nm_list)
{
	t_nm		*tmp;

	tmp = nm_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->str_label, new_nm->str_label) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int				is_magicn_handled(void *sent_ptr)
{
	unsigned int magic_n;

	magic_n = *(unsigned int*)sent_ptr;
	if (magic_n == MH_MAGIC ||
		magic_n == MH_MAGIC_64 ||
		magic_n == FAT_MAGIC ||
		magic_n == FAT_CIGAM ||
		(ft_memcmp(sent_ptr, ARMAG, SARMAG)) == 0)
		return (1);
	return (0);
}
