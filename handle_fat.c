/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 15:40:42 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/27 15:40:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	handle_fat(t_nm *nm, char *file_ptr)
{
	struct fat_header		*fat_head;
	struct fat_arch			*fat_arch_struct;
	unsigned int			i;

	fat_head = (struct fat_header *)file_ptr;
	if (nm->is_reverse_fat_bin == 1)
	{
		// swap endian
	}

	i = 0;
	ft_putstr("nb of fatarch :");
	ft_putnbr(swap32(fat_head->nfat_arch));
	ft_putchar('\n');

	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	while (i < swap32(fat_head->nfat_arch))
	{
		ft_putendl("fat arch");
		fat_arch_struct = (void *)fat_arch_struct + sizeof(*fat_arch_struct);
		i++;
	}
}
