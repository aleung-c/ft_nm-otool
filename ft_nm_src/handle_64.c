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

#include "../includes/ft_nm_otool.h"

char	get_symbol_section_type_64(t_bin64_handler *b, int section_nb,
									char *file_ptr)
{
	unsigned int		i;
	char				ret;

	i = 0;
	b->file_header = (struct mach_header_64 *)file_ptr;
	b->lc = (void *)file_ptr + sizeof(*b->file_header);
	b->section_counter = 0;
	while (i < b->file_header->ncmds)
	{
		if (b->lc->cmd == LC_SEGMENT_64)
		{
			b->sc = (struct segment_command_64 *)b->lc;
			b->sect = (struct section_64 *)((char *)b->sc
					+ sizeof(struct segment_command_64));
			ret = get_symbol_type_sectioncmp_64(b, section_nb);
			if (ret != 0)
				return (ret);
		}
		b->lc = (void *)b->lc + b->lc->cmdsize;
		i++;
	}
	return ('S');
}

char	get_symbol_type_sectioncmp_64(t_bin64_handler *b, int section_nb)
{
	unsigned int		y;

	y = 0;
	if (b->sc->nsects != 0)
	{
		while (y < b->sc->nsects)
		{
			b->section_counter += 1;
			if (b->section_counter == section_nb)
			{
				if (ft_strcmp(b->sect->sectname, SECT_DATA) == 0)
					return ('D');
				else if (ft_strcmp(b->sect->sectname, SECT_BSS) == 0)
					return ('B');
				else if (ft_strcmp(b->sect->sectname, SECT_TEXT) == 0)
					return ('T');
				else
					return ('S');
			}
			b->sect = (struct section_64 *)((char *)b->sect
						+ sizeof(struct section_64));
			y++;
		}
	}
	return (0);
}

char	get_symbol_type_64(t_bin64_handler *b, char *file_ptr, int i)
{
	char ret;

	ret = 0;
	if ((b->list[i].n_type & N_TYPE) == N_UNDF)
	{
		if (b->list[i].n_value)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((b->list[i].n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((b->list[i].n_type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((b->list[i].n_type & N_TYPE) == N_INDR)
		ret = 'I';
	else if ((b->list[i].n_type & N_TYPE) == N_SECT)
		ret = get_symbol_section_type_64(b, b->list[i].n_sect, file_ptr);
	if ((b->list[i].n_type & N_STAB) != 0)
		ret = 'Z';
	if ((b->list[i].n_type & N_EXT) == 0)
		ret = ft_tolower(ret);
	return (ret);
}

void	fill_outputs_64(t_nm *nm, t_bin64_handler *b, char *file_ptr)
{
	t_nm_output					*new_output;
	char						*string_table;
	char						output[16];
	unsigned int				i;

	b->list = (void *)file_ptr + b->symtab->symoff;
	string_table = (void *)file_ptr + b->symtab->stroff;
	i = 0;
	nm->output_list = NULL;
	nm->arch_type = 64;
	while (i < b->symtab->nsyms)
	{
		new_output = (t_nm_output *)malloc(sizeof(t_nm_output));
		new_output->next = NULL;
		new_output->sym_value = b->list[i].n_value;
		to_hex(output, 16, b->list[i].n_value);
		ft_memcpy(new_output->sym_output, output, 16);
		new_output->sym_type = get_symbol_type_64(b, file_ptr, i);
		new_output->sym_str = ft_strdup(string_table + b->list[i].n_un.n_strx);
		if (!(new_output->sym_type == 'Z') && !(new_output->sym_type == 'z'))
			add_output_to_list(nm, new_output);
		i++;
	}
}

void	handle_64(t_nm *nm, char *file_ptr)
{
	t_bin64_handler			b;
	int						i;

	b.file_header = (struct mach_header_64 *)file_ptr;
	b.ncmds = b.file_header->ncmds;
	if (b.file_header->filetype & MH_DYLIB)
		nm->is_dyld = 1;
	b.lc = (void *)file_ptr + sizeof(*b.file_header);
	i = 0;
	while (i < b.ncmds)
	{
		if (b.lc->cmd == LC_SYMTAB)
		{
			b.symtab = (struct symtab_command *)b.lc;
			fill_outputs_64(nm, &b, file_ptr);
		}
		b.lc = (void *)b.lc + b.lc->cmdsize;
		i++;
	}
}
