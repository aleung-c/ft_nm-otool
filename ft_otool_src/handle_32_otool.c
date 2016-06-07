/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32_otool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:41:17 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/06 14:41:20 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

void	fill_ot_output_32(t_nm *nm, struct section *sect, char *ptr_to_text)
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

void handle_32_otool(t_nm *nm, char *file_ptr)
{
	struct mach_header		*file_header;
	struct load_command			*lc;
	struct segment_command	*sc;
	struct section			*sect;
	unsigned int				i;
	unsigned int				y;

	file_header = (struct mach_header *)file_ptr;
	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	nm->arch_type = 32;
	i = 0;

	// run through all loads commands.
	while (i < file_header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT) // only segments can be casted.
		{
			sc = (struct segment_command *)lc;
			if (ft_strcmp(sc->segname, SEG_TEXT) == 0)
			{
				sect = (struct section *)((char *)sc + sizeof(struct segment_command));
				//printf("%s\n", sect->sectname);
				y = 0;
				if (sc->nsects != 0)
				{
					/*ft_putstr("nsect = ");
					ft_putnbr(sc->nsects);
					ft_putchar('\n');*/
					while (y < sc->nsects)
					{
						/*ft_putstr("sect name = ");
						ft_putendl(sect->sectname);

						ft_putstr("sect size = ");
						ft_putnbr(sect->size);
						ft_putchar('\n');*/

						if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
						{
							// print_format_hex_address(buffer, 16, (unsigned long)(sect->addr));
							// ft_putstr(" ");
							fill_ot_output_32(nm, sect, (void *)file_ptr + sect->offset);
							//ptr_to_text = (void *)file_ptr + sect->offset;							
							//printf("%llx", (unsigned long long)((void *)file_ptr + sect->offset));
						}
						// ft_putchar('\n');
						// goto next section;
						sect = (struct section *)((char *)sect + sizeof(struct section));
						y++;
					}
				}
			}
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}