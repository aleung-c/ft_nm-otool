/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_entry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 14:58:11 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/06 14:58:13 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

/*
**	Try opening and treating file. Main function
*/

int		ft_nm(t_nm *nm_list, char **argv, int i)
{
	t_nm		*new_nm;

	while (argv[i])
	{
		new_nm = create_new_nm(argv, i);
		if (new_nm->fd >= 0)
		{
			fstat(new_nm->fd, &(new_nm->file_stat));
			if ((new_nm->file_ptr = mmap(0, new_nm->file_stat.st_size,
				PROT_READ, MAP_PRIVATE, new_nm->fd, 0)) != MAP_FAILED)
			{
				nm_list = add_new_nm_file_to_list(nm_list, new_nm);
				nm_entry(new_nm, new_nm->file_ptr);
			}
			else
				print_error(argv, i, 1);
		}
		else
			print_error(argv, i, 2);
		munmap(new_nm->file_ptr, new_nm->file_stat.st_size);
		i++;
	}
	nm_print_from_list(nm_list, i);
	return (0);
}

t_nm	*create_new_nm(char **argv, int i)
{
	t_nm		*new_nm;

	new_nm = (t_nm *)malloc(sizeof(t_nm));
	new_nm->str_label = ft_strdup(argv[i]);
	new_nm->next = NULL;
	new_nm->fd = open(argv[i], O_RDONLY);
	new_nm->is_ar = 0;
	new_nm->is_ar_member = 0;
	new_nm->is_fat = 0;
	new_nm->is_dyld = 0;
	new_nm->is_err = 0;
	return (new_nm);
}

/*
** check binary type
*/

void	nm_entry(t_nm *nm, char *file_ptr)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)file_ptr;
	if (magic_number == MH_MAGIC)
	{
		handle_32(nm, file_ptr);
	}
	else if (magic_number == MH_MAGIC_64)
	{
		handle_64(nm, file_ptr);
	}
	else if (magic_number == FAT_MAGIC)
	{
		handle_fat(nm, file_ptr);
	}
	else if (magic_number == FAT_CIGAM)
	{
		handle_fat_cigam(nm, file_ptr);
	}
	else if (ft_memcmp(file_ptr, ARMAG, SARMAG) == 0)
	{
		handle_ar(nm, file_ptr);
	}
}
