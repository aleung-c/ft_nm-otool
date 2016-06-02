/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 12:03:48 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/30 12:03:51 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

char	get_symbol_section_type_32(int section_nb, char *file_ptr)
{
	struct mach_header			*file_header;
	struct load_command			*lc;
	struct segment_command		*sc;
	struct section				*sect;
	unsigned int				i;
	unsigned int				y;
	int							section_counter;

	file_header = (struct mach_header *)file_ptr;
	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	i = 0;
	section_counter = 0;
	// run through all loads commands.
	while (i < file_header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT) // only segments can be casted.
		{
			sc = (struct segment_command *)lc;
			sect = (struct section *)((char *)sc + sizeof(struct segment_command));
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
					sect = (struct section *)((char *)sect + sizeof(struct section));
					y++;
				}
			}
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return ('S');
}

void	fill_outputs_32(t_nm *nm, int nsyms, int symoff, int stroff, char *file_ptr)
{
	t_nm_output					*new_output;
	int							i;
	struct nlist				*list;
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
		new_output->arch_type = 32;
		// Fill value
		new_output->sym_value = list[i].n_value;
		to_hex(output, 16, list[i].n_value);
		ft_memcpy(new_output->sym_output, output, 16);

		// Get symbol type
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
			new_output->sym_type = get_symbol_section_type_32(list[i].n_sect, file_ptr);
		if ((list[i].n_type & N_STAB) != 0)
			new_output->sym_type = 'Z';
		if ((list[i].n_type & N_PEXT) != 0 || (list[i].n_type & N_EXT) == 0) // TODO : fonctionne pas tout le temps.
				new_output->sym_type = ft_tolower(new_output->sym_type);
		new_output->sym_str = ft_strdup(string_table + list[i].n_un.n_strx);
		if (!(new_output->sym_type == 'Z') && !(new_output->sym_type == 'z')) // not adding z stuffs.
			add_output_to_list(nm, new_output);
		i++;
	}
}

void handle_32(t_nm *nm, char *file_ptr)
{
	struct mach_header			*file_header;
	struct symtab_command		*symtab;
	struct load_command			*lc;
	int							ncmds;
	int							i;
	
	file_header = (struct mach_header *)file_ptr;
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
			fill_outputs_32(nm, symtab->nsyms, symtab->symoff, symtab->stroff, file_ptr);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

// CIGAM

/*void handle_32_cigam(t_nm *nm, char *file_ptr)
{
	struct mach_header			*file_header;
	struct symtab_command		*symtab;
	struct load_command			*lc;
	int							ncmds;
	int							i;
	
	file_header = (struct mach_header *)file_ptr;
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
			fill_outputs_32(nm, symtab->nsyms, symtab->symoff, symtab->stroff);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}
*/
