/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:20:59 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/27 12:21:01 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

/*
**	Try opening and treating file. Main function
*/
int		try_file_description(t_nm *nm_list, char **argv)
{
	t_nm	*new_nm;
	int i;

	i = 1;
	while (argv[i])
	{

		new_nm = (t_nm *)malloc(sizeof(t_nm));
		// set values
		new_nm->str_label = ft_strdup(argv[i]);
		new_nm->next = NULL;
		new_nm->fd = open(argv[i], O_RDONLY);
		new_nm->is_ar = 0;
		new_nm->is_fat = 0;
		new_nm->is_dyld = 0;
		// check file description.
		if (new_nm->fd >= 0)
		{
			fstat(new_nm->fd, &(new_nm->file_stat));
			if ((new_nm->file_ptr = mmap(0, new_nm->file_stat.st_size,
				PROT_READ, MAP_PRIVATE, new_nm->fd, 0)) != MAP_FAILED)
			{
				//ft_putendl("File seems OK");
				
				nm_list = add_new_nm_file_to_list(nm_list, new_nm);
				// display name of processed argument ?
				/*ft_putstr("process: ");
				ft_putendl(argv[i]);*/
				nm_entry(new_nm, new_nm->file_ptr);
			}
			else
			{
				ft_putstr(argv[0]);
				if (!argv[i])
					ft_putstr(": ./a.out:");
				else
				{
					ft_putstr(": ");
					ft_putstr(argv[1]);
				}
				ft_putendl(": Is a directory or invalid file."); // when opening folder.
				//return (-1);
			}
		}
		else
		{
			ft_putstr(argv[i]);
			if (!argv[1])
				ft_putstr(": ./a.out:");
			else
			{
				ft_putstr(": ");
				ft_putstr(argv[i]);
			}
			ft_putendl(": No such file or directory.");
		
		}		
		munmap(new_nm->file_ptr, new_nm->file_stat.st_size);
		i++;
	}
	nm_print_from_list(nm_list, i);
	return (0);
}
