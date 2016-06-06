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

void	handle_64_otool(t_nm *nm, char *file_ptr)
{
	struct mach_header_64		*file_header;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	struct section_64			*sect;
	unsigned int				i;
	unsigned int				y;

	if (nm)
	{}
	file_header = (struct mach_header_64 *)file_ptr;
	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	i = 0;
	// run through all loads commands.
	while (i < file_header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64) // only segments can be casted.
		{
			sc = (struct segment_command_64 *)lc;
			if (ft_strcmp(sc->segname, SEG_TEXT))
			{
				sect = (struct section_64 *)((char *)sc + sizeof(struct segment_command_64));
				y = 0;
				if (sc->nsects != 0)
				{
					while (y < sc->nsects)
					{
						if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
						{
							printf("%x", (unsigned int)((void *)file_ptr + sect->offset));
						}
						// goto next section;
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
