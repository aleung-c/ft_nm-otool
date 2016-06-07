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

#include "../includes/ft_nm_otool.h"

void	handle_fat(t_nm *nm, char *file_ptr)
{
	t_fatbin_handler			b;
	char						*sent_file_ptr;
	unsigned int				i;

	i = 0;
	b.fat_head = (struct fat_header *)file_ptr;
	nm->is_fat = 1;
	b.fat_arch_struct = (void *)b.fat_head + sizeof(*b.fat_head);
	while (i < b.fat_head->nfat_arch)
	{
		sent_file_ptr = (void *)file_ptr + b.fat_arch_struct->offset;
		if (search_for_64_arch(&b, sent_file_ptr, file_ptr) == 1)
		{
			nm_entry(nm, (void *)file_ptr + b.fat_arch_struct->offset);
			return ;
		}
		b.fat_arch_struct = (void *)b.fat_arch_struct
							+ sizeof(*b.fat_arch_struct);
		i++;
	}
	b.fat_arch_struct = (void *)b.fat_head + sizeof(*b.fat_head);
	nm_entry(nm, (void *)file_ptr + b.fat_arch_struct->offset);
}

int		search_for_64_arch(t_fatbin_handler *b, char *sent_file_ptr,
							char *file_ptr)
{
	struct ar_hdr			*ar_header;
	unsigned int			ar_size;
	unsigned int			offset_size;
	unsigned int			magic_number;

	magic_number = *(unsigned int *)((void *)file_ptr
					+ b->fat_arch_struct->offset);
	if (magic_number == MH_MAGIC_64)
		return (1);
	else if (ft_memcmp(sent_file_ptr, ARMAG, SARMAG) == 0)
	{
		ar_header = (void *)sent_file_ptr + SARMAG;
		ar_size = str_to_int(ar_header->ar_size);
		offset_size = str_to_int((void *)ar_header + 3);
		ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
		magic_number = *(unsigned int *)((void *)ar_header
						+ sizeof(*ar_header) + offset_size);
		if (magic_number == MH_MAGIC_64)
			return (1);
	}
	return (0);
}

int		search_for_64_arch_cigam(t_fatbin_handler *b,
						char *sent_file_ptr, char *file_ptr)
{
	struct ar_hdr			*ar_header;
	unsigned int			ar_size;
	unsigned int			offset_size;
	unsigned int			magic_number;

	magic_number = *(unsigned int *)((void *)file_ptr
					+ (swap32(b->fat_arch_struct->offset)));
	if (magic_number == MH_MAGIC_64)
		return (1);
	else if (ft_memcmp(sent_file_ptr, ARMAG, SARMAG) == 0)
	{
		ar_header = (void *)sent_file_ptr + SARMAG;
		ar_size = str_to_int(ar_header->ar_size);
		offset_size = str_to_int((void *)ar_header + 3);
		ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
		magic_number = *(unsigned int *)((void *)ar_header
						+ sizeof(*ar_header) + offset_size);
		if (magic_number == MH_MAGIC_64)
			return (1);
	}
	return (0);
}

void	handle_fat_cigam(t_nm *nm, char *file_ptr)
{
	t_fatbin_handler			b;
	char						*sent_file_ptr;
	unsigned int				i;

	i = 0;
	b.fat_head = (struct fat_header *)file_ptr;
	nm->is_fat = 1;
	b.fat_arch_struct = (void *)b.fat_head + sizeof(*b.fat_head);
	while (i < swap32(b.fat_head->nfat_arch))
	{
		sent_file_ptr = (void *)file_ptr
						+ swap32(b.fat_arch_struct->offset);
		if (search_for_64_arch_cigam(&b, sent_file_ptr, file_ptr) == 1)
		{
			nm_entry(nm, (void *)file_ptr
						+ (swap32(b.fat_arch_struct->offset)));
			return ;
		}
		b.fat_arch_struct = (void *)b.fat_arch_struct
							+ sizeof(*b.fat_arch_struct);
		i++;
	}
	b.fat_arch_struct = (void *)b.fat_head + sizeof(*b.fat_head);
	nm_entry(nm, (void *)file_ptr
				+ (swap32(b.fat_arch_struct->offset)));
}
