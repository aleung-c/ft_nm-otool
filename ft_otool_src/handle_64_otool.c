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

void	fill_ot_output_64(t_nm *nm, struct section_64 *sect,
							char *ptr_to_text)
{
	t_ot_output		*new_output;

	new_output = (t_ot_output *)malloc(sizeof(t_ot_output));
	new_output->next = NULL;
	new_output->sect_addr = sect->addr;
	ft_memcpy(new_output->sect_name, sect->sectname, 16);
	ft_memcpy(new_output->seg_name, sect->segname, 16);
	new_output->sect_size = sect->size;
	new_output->sect_mem = (char *)malloc(new_output->sect_size
							* sizeof(char));
	ft_memcpy(new_output->sect_mem, ptr_to_text, new_output->sect_size);
	add_ot_output_to_list(nm, new_output);
}

void	handle_64_otool(t_nm *nm, char *file_ptr)
{
	t_bin64_handler				b;

	b.file_header = (struct mach_header_64 *)file_ptr;
	b.lc = (void *)file_ptr + sizeof(*b.file_header);
	nm->arch_type = 64;
	if (b.file_header->filetype == MH_OBJECT)
	{
		handle_64_mh_object(nm, &b, file_ptr);
	}
	else
	{
		handle_64_regular_object(nm, &b, file_ptr);
	}
}

void	handle_64_regular_object(t_nm *nm, t_bin64_handler *b,
								char *file_ptr)
{
	unsigned int i;

	i = 0;
	while (i < b->file_header->ncmds)
	{
		if (b->lc->cmd == LC_SEGMENT_64)
		{
			b->sc = (struct segment_command_64 *)b->lc;
			if (ft_strcmp(b->sc->segname, SEG_TEXT) == 0)
				handle_64_regular_section_run(nm, b, file_ptr);
		}
		b->lc = (void *)b->lc + b->lc->cmdsize;
		i++;
	}
}

void	handle_64_regular_section_run(t_nm *nm, t_bin64_handler *b,
									char *file_ptr)
{
	unsigned int y;

	b->sect = (struct section_64 *)((char *)b->sc
					+ sizeof(struct segment_command_64));
	y = 0;
	if (b->sc->nsects != 0)
	{
		while (y < b->sc->nsects)
		{
			if (ft_strcmp(b->sect->sectname, SECT_TEXT) == 0)
				fill_ot_output_64(nm, b->sect, (void *)file_ptr
					+ b->sect->offset);
			b->sect = (struct section_64 *)((char *)b->sect
				+ sizeof(struct section_64));
			y++;
		}
	}
}

void	handle_64_mh_object(t_nm *nm, t_bin64_handler *b, char *file_ptr)
{
	unsigned int y;

	b->sc = (struct segment_command_64 *)b->lc;
	b->sect = (struct section_64 *)((char *)b->sc
				+ sizeof(struct segment_command_64));
	y = 0;
	if (b->sc->nsects != 0)
	{
		while (y < b->sc->nsects)
		{
			if (ft_strcmp(b->sect->sectname, SECT_TEXT) == 0)
				fill_ot_output_64(nm, b->sect, (void *)file_ptr
									+ b->sect->offset);
			b->sect = (struct section_64 *)((char *)b->sect
						+ sizeof(struct section_64));
			y++;
		}
	}
}
