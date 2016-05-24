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

void	to_hex(char *buffer, size_t size, unsigned n)
{
	size_t		i;
	size_t		j;
	char		c;
	unsigned	digit;

	i = 0;
	while (i < size)
	{
		digit = n & 0xf;
		buffer[i] = digit < 10 ? digit + '0' : digit - 10 + 'a';
		n >>= 4;
		if (n == 0)
			break ;
		i++;
	}
	buffer[i + 1] = 0;
	j = 0;
	while (j < i / 2)
	{
		c = buffer[j];
		buffer[j] = buffer[i - j];
		buffer[i - j] = c;
		++j;
	}
}


void	print_symbols(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	struct nlist_64		*list;
	char				*string_table;
	char				output[12];

	list = (void *)ptr + symoff;
	string_table = (void *)ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		to_hex(output, 12, list[i].n_value);
		ft_putstr(output);
		ft_putstr(" ");
		ft_putstr(string_table + list[i].n_un.n_strx);
		ft_putchar('\n');
		i++;
	}
}

void	handle_64bin(t_nm *nm, char *file_ptr)
{
	struct mach_header_64	*file_header;
	struct symtab_command	*symtab;
	struct load_command		*lc;
	int						ncmds;
	int						i;

	if (nm)
	{}
	file_header = (struct mach_header_64 *)file_ptr;
	ncmds = file_header->ncmds;
	ft_putstr("ncmds :");
	ft_putnbr(ncmds);
	ft_putchar('\n');
	lc = (void *)file_ptr + sizeof(*file_header); // move past the header.
	i = 0;
	// run through all loads commands.
	while (i < ncmds)
	{
		// must find symbol tab load command;
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *)lc;

			ft_putstr("nb symbols :");
			ft_putnbr(symtab->nsyms);
			ft_putchar('\n');
			print_symbols(symtab->nsyms, symtab->symoff, symtab->stroff, file_ptr);
			break; // the rest is not needed right now;
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
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		// fat file.
		ft_putendl("bin fat");
	}
	else if (magic_number == MH_SPLIT_SEGS)
	{
		ft_putendl("multiple segs");
	}
	else // ???
	{
		ft_putendl("unhandled file type");
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