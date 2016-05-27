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



void	add_output_to_list(t_nm *nm, t_nm_output *new_output)
{
	t_nm_output			*tmp;

	if (nm->output_list == NULL)
	{
		nm->output_list = new_output;
	}
	else
	{
		tmp = nm->output_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_output;
	}
}

/*
** check binary type
*/
void	nm_entry(t_nm *nm, char *file_ptr)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)file_ptr;
	if (magic_number == MH_MAGIC_64)
	{
		// 64bit exec file;
		//ft_putendl("bin 64bit");
		handle_64(nm, file_ptr);
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
		nm->is_fat_bin = 1;
		nm->is_reverse_fat_bin = 0;
		ft_putendl("bin fat");
		handle_fat(nm, file_ptr);
	}
	else if (magic_number == FAT_CIGAM)
	{
		nm->is_fat_bin = 1;
		nm->is_reverse_fat_bin = 1;
		// fat file endian reversed.
		ft_putendl("bin fat cigam");
		handle_fat(nm, file_ptr);
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
**	First logical parse if needed
*/
void		parse_args(int argc, char **argv)
{
	if (argc == 1)
	{
		argv[1] = ft_strdup("a.out"); // bug. a revoir
	}
}

int		main(int argc, char **argv)
{
	t_nm	*nm_list; // file chained list;

	nm_list = NULL;
	parse_args(argc, argv);
	if (try_file_description(nm_list, argv) != 0)
		return (-1);
	return (0);
}