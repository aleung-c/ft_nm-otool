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

	fat_head = (struct fat_header *)file_ptr;
	/*ft_putstr("nb of fatarch :");
	ft_putnbr(fat_head->nfat_arch);
	ft_putchar('\n');*/
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	nm_entry(nm, (void *)file_ptr + fat_arch_struct->offset);
}

void	handle_fat_cigam(t_nm *nm, char *file_ptr)
{
	struct fat_header		*fat_head;
	struct fat_arch			*fat_arch_struct;

	fat_head = (struct fat_header *)file_ptr;
	/*ft_putstr("nb of fatarch :");
	ft_putnbr(swap32(fat_head->nfat_arch));
	ft_putchar('\n');*/
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	nm_entry(nm, (void *)file_ptr + (swap32(fat_arch_struct->offset)));
}
