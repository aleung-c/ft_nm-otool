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
	// unsigned int	sect_size_counter;
	// char			buffer[16];
	//unsigned long long i;
	new_output = (t_ot_output *)malloc(sizeof(t_ot_output));
	new_output->next = NULL;

	new_output->sect_addr = sect->addr;
	ft_memcpy(new_output->sect_name, sect->sectname , 16);
	ft_memcpy(new_output->seg_name, sect->segname , 16);
	new_output->sect_size = sect->size;
	new_output->sect_mem = (char *)malloc(new_output->sect_size * sizeof(char));
	ft_memcpy(new_output->sect_mem, ptr_to_text, new_output->sect_size);
	//new_output->sect_mem = ptr_to_text;
	// i = 0;
	// while (i < sect->size)
	// {
	// 	new_output->sect_mem[i] = ptr_to_text[i];
	// 	i++;
	// }
	
	add_ot_output_to_list(nm, new_output);
	
	/*
	sect_size_counter = 0;
	while (sect_size_counter < sect->size)
	{
		if (sect_size_counter % 16 == 0)
		{
			ft_putchar('\n');
			print_format_hex_address(buffer, 16, (unsigned long)((void *)sect->addr + sect_size_counter));
			ft_putstr(" ");
		}
		
		ft_putnbytes(buffer, 2, *(char *)(ptr_to_text));
		ft_putchar(' ');
		//ft_putnbytes(buffer, 16, *(unsigned long *)(ptr_to_text + sizeof(unsigned long)));
		//ft_putchar('\n');
		ptr_to_text = (char *)ptr_to_text + 1;
		sect_size_counter += (sizeof(char));
	}
	*/
}

void	handle_64_otool(t_nm *nm, char *file_ptr)
{
	struct mach_header_64		*file_header;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	struct section_64			*sect;
	unsigned int				i;
	unsigned int				y;
	//char 						buffer[16];
	//unsigned int				sect_size_counter;

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
			if (ft_strcmp(sc->segname, SEG_TEXT) == 0)
			{
				sect = (struct section_64 *)((char *)sc + sizeof(struct segment_command_64));
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
							fill_ot_output_64(nm, sect, (void *)file_ptr + sect->offset);
							//ptr_to_text = (void *)file_ptr + sect->offset;							
							//printf("%llx", (unsigned long long)((void *)file_ptr + sect->offset));
						}
						// ft_putchar('\n');
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
