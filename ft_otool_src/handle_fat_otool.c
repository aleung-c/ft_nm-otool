/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_otool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:41:30 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/06 14:41:32 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void	handle_fat_otool(t_nm *nm, char *file_ptr)
{
	struct fat_header		*fat_head;
	struct fat_arch			*fat_arch_struct;
	unsigned int			i;
	unsigned int			magic_number;

	i = 0;
	fat_head = (struct fat_header *)file_ptr;
	nm->is_fat = 1;
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	while (i < fat_head->nfat_arch)
	{
		magic_number = *(unsigned int *)(void *)file_ptr + (fat_arch_struct->offset);
		if (magic_number == MH_MAGIC_64)
		{
			otool_entry(nm, (void *)file_ptr + fat_arch_struct->offset);
			return ;
		}
		fat_arch_struct = (void *)fat_arch_struct + sizeof(*fat_arch_struct);
		i++;
	}
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	otool_entry(nm, (void *)file_ptr + fat_arch_struct->offset);
}

void	handle_fat_cigam_otool(t_nm *nm, char *file_ptr)
{
	struct fat_header		*fat_head;
	struct fat_arch			*fat_arch_struct;
	unsigned int			i;
	unsigned int			magic_number;
	char					*sent_file_ptr;

	struct ar_hdr			*ar_header;
	unsigned int			ar_size;
	unsigned int			offset_size;

	i = 0;
	fat_head = (struct fat_header *)file_ptr;
	nm->is_fat = 1;
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	while (i < swap32(fat_head->nfat_arch))
	{
		sent_file_ptr = (void *)file_ptr + swap32(fat_arch_struct->offset);
		magic_number = *(unsigned int *)sent_file_ptr;
		if (magic_number == MH_MAGIC_64)
		{
			otool_entry(nm, sent_file_ptr);
			return ;
		}
		else if (ft_memcmp(sent_file_ptr, ARMAG, SARMAG) == 0)
		{
			ar_header = (void *)sent_file_ptr + SARMAG;
			ar_size = str_to_int(ar_header->ar_size);
			offset_size = str_to_int((void *)ar_header + 3);
			ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
			magic_number = *(unsigned int *)((void *)ar_header + sizeof(*ar_header) + offset_size);
			if (magic_number == MH_MAGIC_64)
			{
				otool_entry(nm, sent_file_ptr);
				return ;
			}
		}
		fat_arch_struct = (void *)fat_arch_struct + sizeof(*fat_arch_struct);
		i++;
	}
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	otool_entry(nm, (void *)file_ptr + (swap32(fat_arch_struct->offset)));
}