/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 18:03:15 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/23 18:03:25 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

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
						if (ft_strcmp(sect->segname, "__TEXT") == 0)
							return ('T');
						else if (ft_strcmp(sect->segname, "__DATA") == 0)
							return ('D');
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

void	print_symbols(struct load_command *lc, int nsyms, int symoff, int stroff, char *ptr)
{
	int							i;
	struct nlist_64				*list;
	char						*string_table;
	char						output[16];
	
	if (lc)
	{}

	list = (void *)ptr + symoff;
	string_table = (void *)ptr + stroff;
	i = 0;

	while (i < nsyms)
	{
		// print value
		if (list[i].n_value != 0x0)
		{
			to_hex(output, 16, list[i].n_value);
			print_format_hex_address(output);
			ft_putstr(" ");
		}
		else
		{
			ft_putstr("                ");
		}
		// print type
		if ((list[i].n_type & N_TYPE) == N_UNDF)
			ft_putstr(" U "); // undefined
		else if ((list[i].n_type & N_TYPE) == N_ABS)
			ft_putstr(" A "); // absolute
		else if ((list[i].n_type & N_TYPE) == N_SECT)
		{
			ft_putchar(get_symbol_section_type_64(list[i].n_sect, ptr)); // need to go check the section.
			ft_putstr(" ");
		}
		else
			ft_putstr(" S "); // in an uninitialized data section.

		// print symbol name;
		ft_putstr(string_table + list[i].n_un.n_strx);
		ft_putchar('\n');
		i++;
	}
}

void	handle_64bin(t_nm *nm, char *file_ptr)
{
	struct mach_header_64		*file_header;
	struct symtab_command		*symtab;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	struct section_64			*sect;
	int							ncmds;
	int							i;
	unsigned int				y;

	if (nm)
	{}
	ft_putendl(" // DEBUG dump file ------- //");
	file_header = (struct mach_header_64 *)file_ptr;
	ncmds = file_header->ncmds;

	/*ft_putstr("ncmds :");
	ft_putnbr(ncmds);
	ft_putchar('\n');*/

	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	i = 0;
	// run through all loads commands.
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64) // only segments can be casted.
		{
			sc = (struct segment_command_64 *)lc;
			if (!sc)
				break;
			ft_putstr("segname :");
			ft_putstr(sc->segname);
			ft_putchar('\n');

			/*ft_putstr("seg->sect nb :");
			ft_putnbr(sc->nsects);
			ft_putchar('\n');*/

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

		// must find symbol tab load command;
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *)lc;

			ft_putstr("nb symbols :");
			ft_putnbr(symtab->nsyms);
			ft_putchar('\n');
			print_symbols(lc, symtab->nsyms, symtab->symoff, symtab->stroff, file_ptr);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}


/*
** check binary type
*/
void	nm_entry(t_nm *nm, char *file_ptr)
{
	unsigned int		magic_number;

	if (nm)
	{}

	magic_number = *(unsigned int *)file_ptr;
	if (magic_number == MH_MAGIC_64)
	{
		// 64bit exec file;
		ft_putendl("bin 64bit");
		handle_64bin(nm, file_ptr);
	}
	else if (magic_number == MH_MAGIC)
	{
		// 32bit exec file;
		ft_putendl("bin 32bit");
	}
	else if (magic_number == MH_DYLIB)
	{
		ft_putendl("bin dynamic lib");
	}
	else if (magic_number == FAT_MAGIC)
	{
		// fat file.
		ft_putendl("bin fat");
	}
	else if (magic_number == FAT_CIGAM)
	{
		// fat file endian reversed.
		ft_putendl("bin fat cigam");
	}
	else if (ft_memcmp(file_ptr, "!<arch>\n", 8) == 0)
	{
		ft_putendl("Lib");
	}
	else // ???
	{
		ft_putendl("Unhandled file type");
		return ;
	}
}

/*
**	Try opening and converting binary file to char *.
*/
int		try_file_description(t_nm *nm, char **argv)
{
	// faire boucle des args;
	// open try;
	nm->fd = open(argv[1], O_RDONLY);
	if (nm->fd > 0)
	{
		fstat(nm->fd, &(nm->file_stat));
	 	if ((nm->file_ptr = mmap(0, nm->file_stat.st_size,
	 		PROT_READ, MAP_PRIVATE, nm->fd, 0)) != MAP_FAILED)
	 	{
	 		ft_putendl("File seems OK");
	 		nm_entry(nm, nm->file_ptr);
	 		return (0);
	 	}
	 	else
	 	{
	 		ft_putendl("mmap error"); // when opening folder.
	 		return (-1);
	 	}
	}
	else
	{
		ft_putendl("open error"); // file doesnt exist;
		return (-1);
	}
	if (munmap(nm->file_ptr, nm->file_stat.st_size) < 0)
	{
		ft_putendl("munmap error");
		return (-1);
	}
	return (0);
}

/*
**	First logical parse if needed
*/
int		parse_args(char **argv)
{
	if (argv)
	{}
	return (0);
}

int		main(int argc, char **argv)
{
	t_nm	nm;

	if (argc > 1 && (parse_args(argv)) == 0)
	{
		if (try_file_description(&nm, argv) != 0)
			return (-1);
	}
	else
	{
		ft_putendl("no args.");
		// must try with a.out
	}
	return (0);
}