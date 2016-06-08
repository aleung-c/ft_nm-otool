/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_searchers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 12:01:25 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/08 12:01:31 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

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

void	*get_valid_arch(t_fatbin_handler *b, char *file_ptr)
{
	unsigned int		i;
	void				*ret;

	i = 0;
	b->fat_arch_struct = (void *)b->fat_head + sizeof(*b->fat_head);
	while (i < (b->fat_head->nfat_arch))
	{
		ret = (void *)file_ptr
						+ b->fat_arch_struct->offset;
		if (is_magicn_handled(ret))
			return (ret);
		b->fat_arch_struct = (void *)b->fat_arch_struct
							+ sizeof(*b->fat_arch_struct);
		i++;
	}
	b->fat_arch_struct = (void *)b->fat_head + sizeof(*b->fat_head);
	return ((void *)file_ptr
				+ b->fat_arch_struct->offset);
}

void	*get_valid_arch_cigam(t_fatbin_handler *b, char *file_ptr)
{
	unsigned int		i;
	void				*ret;

	i = 0;
	b->fat_arch_struct = (void *)b->fat_head + sizeof(*b->fat_head);
	while (i < (swap32(b->fat_head->nfat_arch)))
	{
		ret = (void *)file_ptr
						+ (swap32(b->fat_arch_struct->offset));
		if (is_magicn_handled(ret))
			return (ret);
		b->fat_arch_struct = (void *)b->fat_arch_struct
							+ sizeof(*b->fat_arch_struct);
		i++;
	}
	b->fat_arch_struct = (void *)b->fat_head + sizeof(*b->fat_head);
	return ((void *)file_ptr
				+ swap32(b->fat_arch_struct->offset));
}
