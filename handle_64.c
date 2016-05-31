/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 15:40:17 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/27 15:40:22 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

/*void	debug_dump_file_sections_64(t_nm *nm, char *file_ptr)
{
	struct mach_header_64		*file_header;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	struct section_64			*sect;
	int							ncmds;
	int							i;
	unsigned int				y;

	ft_putendl(" // DEBUG dump file ------- //");
	file_header = (struct mach_header_64 *)file_ptr;
	ncmds = file_header->ncmds;
	lc = (void *)file_header + sizeof(*file_header);
	ft_putstr("ncmds :");
	ft_putnbr(ncmds);
	ft_putchar('\n');

	if (nm)
	{
	}
	i = 0;
	// run through all loads commands.
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64) // only segments can be casted.
		{
			sc = (struct segment_command_64 *)lc;

			ft_putstr("segname :");
			ft_putstr(sc->segname);
			ft_putchar('\n');

			ft_putstr("seg->sect nb :");
			ft_putnbr(sc->nsects);
			ft_putchar('\n');

			sect = (struct section_64 *)((char *)sc + sizeof(struct segment_command_64));
			y = 0;
			if (sc->nsects != 0)
			{
				while (y < sc->nsects)
				{
					ft_putstr("sectname :");
					ft_putstr(sect->sectname);
					ft_putchar('\n');
					sect = (struct section_64 *)((char *)sect + sizeof(struct section_64));
					y++;
				}
			}
		}
	}
}*/

char get_symbol_section_type_64(int section_nb, char *file_ptr)
{
	struct mach_header_64		*file_header;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	struct section_64			*sect;
	unsigned int				i;
	unsigned int				y;
	int							section_counter;

	file_header = (struct mach_header_64 *)file_ptr;
	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	i = 0;
	section_counter = 0;
	// run through all loads commands.
	while (i < file_header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64) // only segments can be casted.
		{
			sc = (struct segment_command_64 *)lc;
			sect = (struct section_64 *)((char *)sc + sizeof(struct segment_command_64));
			y = 0;
			if (sc->nsects != 0)
			{
				while (y < sc->nsects)
				{
					section_counter += 1;
					if (section_counter == section_nb)
					{
						// reached asked section.
						if (ft_strcmp(sect->sectname, SECT_DATA) == 0)
							return ('D');
						else if (ft_strcmp(sect->sectname, SECT_BSS) == 0)
							return ('B');
						else if (ft_strcmp(sect->sectname, SECT_TEXT) == 0)
							return ('T');
						else
							return ('S');
					}
					// goto next section;
					sect = (struct section_64 *)((char *)sect + sizeof(struct section_64));
					y++;
				}
			}
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return ('S');
}

void	fill_outputs_64(t_nm *nm, int nsyms, int symoff, int stroff, char *file_ptr)
{
	t_nm_output					*new_output;
	int							i;
	struct nlist_64				*list;
	char						*string_table;
	char						output[16];

	list = (void *)file_ptr + symoff;
	string_table = (void *)file_ptr + stroff;
	i = 0;
	nm->output_list = NULL;
	while (i < nsyms)
	{
		new_output = (t_nm_output *)malloc(sizeof(t_nm_output));
		new_output->next = NULL;
		new_output->arch_type = 64;

		// Fill value
		new_output->sym_value = list[i].n_value;
		to_hex(output, 16, list[i].n_value);
		ft_memcpy(new_output->sym_output, output, 16);

		// get type
		if ((list[i].n_type & N_TYPE) == N_UNDF)
		{
			if (list[i].n_value)
				new_output->sym_type = 'C';
			else
				new_output->sym_type = 'U'; // undefined
		}
		else if ((list[i].n_type & N_TYPE) == N_ABS)
			new_output->sym_type = 'A'; // absolute
		else if ((list[i].n_type & N_TYPE) == N_PBUD)
			new_output->sym_type = 'U'; // undefined
		else if ((list[i].n_type & N_TYPE) == N_INDR)
			new_output->sym_type = 'I';
		else if ((list[i].n_type & N_TYPE) == N_SECT)
			new_output->sym_type = get_symbol_section_type_64(list[i].n_sect, file_ptr);
		if ((list[i].n_type & N_STAB) != 0)
			new_output->sym_type = 'Z';
		if (list[i].n_type & N_PEXT)
				new_output->sym_type = ft_tolower(new_output->sym_type);
		new_output->sym_str = ft_strdup(string_table + list[i].n_un.n_strx);
		add_output_to_list(nm, new_output);
		i++;
	}
}

void	handle_64(t_nm *nm, char *file_ptr)
{
	struct mach_header_64		*file_header;
	struct symtab_command		*symtab;
	struct load_command			*lc;
	int							ncmds;
	int							i;
	
	file_header = (struct mach_header_64 *)file_ptr;
	ncmds = file_header->ncmds;

	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	i = 0;
	// run through all loads commands.
	while (i < ncmds)
	{
		// must find symbol tab load command;
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *)lc;
			fill_outputs_64(nm, symtab->nsyms, symtab->symoff, symtab->stroff, file_ptr);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}
