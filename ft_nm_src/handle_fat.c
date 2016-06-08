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
	unsigned int				i;
	unsigned int				narch;

	i = 0;
	b.fat_head = (struct fat_header *)file_ptr;
	nm->is_fat = 1;
	b.fat_arch_struct = (void *)b.fat_head + sizeof(*b.fat_head);
	narch = b.fat_head->nfat_arch;
	while (i < narch)
	{
		if (search_for_64_arch(&b, ((void *)file_ptr
					+ b.fat_arch_struct->offset), file_ptr) == 1)
		{
			nm_entry(nm, (void *)file_ptr + b.fat_arch_struct->offset);
			return ;
		}
		b.fat_arch_struct = (void *)b.fat_arch_struct
							+ sizeof(*b.fat_arch_struct);
		i++;
	}
	nm_entry(nm, get_valid_arch(&b, file_ptr));
}

void	handle_fat_cigam(t_nm *nm, char *file_ptr)
{
	t_fatbin_handler			b;
	unsigned int				i;
	unsigned int				narch;

	i = 0;
	b.fat_head = (struct fat_header *)file_ptr;
	nm->is_fat = 1;
	b.fat_arch_struct = (void *)b.fat_head + sizeof(*b.fat_head);
	narch = (swap32(b.fat_head->nfat_arch));
	while (i < narch)
	{
		if (search_for_64_arch_cigam(&b, ((void *)file_ptr
					+ swap32(b.fat_arch_struct->offset)), file_ptr) == 1)
		{
			nm_entry(nm, (void *)file_ptr
						+ (swap32(b.fat_arch_struct->offset)));
			return ;
		}
		b.fat_arch_struct = (void *)b.fat_arch_struct
							+ sizeof(*b.fat_arch_struct);
		i++;
	}
	nm_entry(nm, get_valid_arch_cigam(&b, file_ptr));
}
