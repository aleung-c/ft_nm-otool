/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_otool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:41:09 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/06 14:41:11 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void	fill_ot_output_64(t_nm *nm, struct section_64 *sect, char *ptr_to_text)
{
	t_ot_output		*new_output;

	new_output = (t_ot_output *)malloc(sizeof(t_ot_output));
	new_output->next = NULL;
	new_output->sect_addr = sect->addr;
	ft_memcpy(new_output->sect_name, sect->sectname , 16);
	ft_memcpy(new_output->seg_name, sect->segname , 16);
	new_output->sect_size = sect->size;
	new_output->sect_mem = (char *)malloc(new_output->sect_size * sizeof(char));
	ft_memcpy(new_output->sect_mem, ptr_to_text, new_output->sect_size);
	add_ot_output_to_list(nm, new_output);
}

void	handle_64_otool(t_nm *nm, char *file_ptr)
{
	struct mach_header_64		*file_header;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	struct section_64			*sect;
	unsigned int				i;
	unsigned int				y;

	file_header = (struct mach_header_64 *)file_ptr;
	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	nm->arch_type = 64;
	i = 0;
	if (file_header->filetype == MH_OBJECT)
	{
		sc = (struct segment_command_64 *)lc;
		sect = (struct section_64 *)((char *)sc + sizeof(struct segment_command_64));
		y = 0;
		if (sc->nsects != 0)
		{
			while (y < sc->nsects)
			{
				if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
					fill_ot_output_64(nm, sect, (void *)file_ptr + sect->offset);
				sect = (struct section_64 *)((char *)sect + sizeof(struct section_64));
				y++;
			}
		}
	}
	else
	{
		while (i < file_header->ncmds)
		{
			if (lc->cmd == LC_SEGMENT_64)
			{
				sc = (struct segment_command_64 *)lc;
				if (ft_strcmp(sc->segname, SEG_TEXT) == 0)
				{
					sect = (struct section_64 *)((char *)sc + sizeof(struct segment_command_64));
					y = 0;
					if (sc->nsects != 0)
					{
						while (y < sc->nsects)
						{
							if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
							{
								fill_ot_output_64(nm, sect, (void *)file_ptr + sect->offset);
							}
							sect = (struct section_64 *)((char *)sect + sizeof(struct section_64));
							y++;
						}
					}
				}
			}
			lc = (void *)lc + lc->cmdsize;
			i++;
		}
	}
}
