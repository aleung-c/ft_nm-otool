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
#include <stdio.h>

void	handle_fat(t_nm *nm, char *file_ptr)
{
	struct fat_header		*fat_head;
	struct fat_arch			*fat_arch_struct;
	unsigned int			i;
	unsigned int			magic_number;


	i = 0;
	fat_head = (struct fat_header *)file_ptr;
	nm->is_fat = 1;
	/*ft_putstr("nb of fatarch :");
	ft_putnbr(fat_head->nfat_arch);
	ft_putchar('\n');*/

	// Search for 64 bit architecture.
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	while (i < fat_head->nfat_arch)
	{
		magic_number = *(unsigned int *)(void *)file_ptr + (fat_arch_struct->offset);
		if (magic_number == MH_MAGIC_64)
		{
			nm_entry(nm, (void *)file_ptr + fat_arch_struct->offset);
			return ;
		}
		fat_arch_struct = (void *)fat_arch_struct + sizeof(*fat_arch_struct);
		i++;
	}
	// else default == first arch;
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	nm_entry(nm, (void *)file_ptr + fat_arch_struct->offset);
}

void	handle_fat_cigam(t_nm *nm, char *file_ptr) // TODO : ne fonctionne pas.
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
	/*ft_putstr("nb of fatarch :");
	ft_putnbr(swap32(fat_head->nfat_arch));
	ft_putchar('\n');*/

	// Search for 64 bit architecture.
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	while (i < swap32(fat_head->nfat_arch))
	{
		sent_file_ptr = (void *)file_ptr + swap32(fat_arch_struct->offset);
		magic_number = *(unsigned int *)sent_file_ptr;
		if (magic_number == MH_MAGIC_64)
		{
			nm_entry(nm, sent_file_ptr);
			return ;
		}
		else if (ft_memcmp(sent_file_ptr, ARMAG, SARMAG) == 0) // handling fat bin lib...
		{
			ar_header = (void *)sent_file_ptr + SARMAG;

			ar_size = str_to_int(ar_header->ar_size);
			offset_size = str_to_int((void *)ar_header + 3);
			// advance from one;
			ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
			// advance from one;
			magic_number = *(unsigned int *)((void *)ar_header + sizeof(*ar_header) + offset_size);
			if (magic_number == MH_MAGIC_64)
			{
				nm_entry(nm, sent_file_ptr);
				return ;
			}
		}
		fat_arch_struct = (void *)fat_arch_struct + sizeof(*fat_arch_struct);
		i++;
	}

	/*sent_file_ptr = (void *)file_ptr + (swap32(fat_arch_struct->offset));
	magic_number = *(unsigned int *)sent_file_ptr;
	print_format_hex_address(buf, 16, magic_number);
	ft_putchar('\n');*/
	// else default == first arch;
	//fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	fat_arch_struct = (void *)fat_head + sizeof(*fat_head);
	nm_entry(nm, (void *)file_ptr + (swap32(fat_arch_struct->offset)));
}

int		nm_search_64(char *file_ptr)
{
	unsigned int		magic_number;
	char				buf[16];

	
	magic_number = *(unsigned int *)file_ptr;
	print_format_hex_address(buf, 16, magic_number);
	ft_putchar('\n');
	if (magic_number == MH_MAGIC_64)
	{
		return (1);
	}
	return (0);
}


