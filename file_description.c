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
**	Try opening and converting binary file to char *.
*/
int		try_file_description(t_nm *nm_list, char **argv)
{
	t_nm	*new_nm;
	int i;

	i = 1;
	while (argv[i])
	{
		new_nm = (t_nm *)malloc(sizeof(t_nm));
		new_nm->next = NULL;
		new_nm->fd = open(argv[i], O_RDONLY);
		if (new_nm->fd > 0)
		{
			fstat(new_nm->fd, &(new_nm->file_stat));
		 	if ((new_nm->file_ptr = mmap(0, new_nm->file_stat.st_size,
		 		PROT_READ, MAP_PRIVATE, new_nm->fd, 0)) != MAP_FAILED)
		 	{
		 		//ft_putendl("File seems OK");
		 		nm_list = add_new_nm_file_to_list(nm_list, new_nm);
		 		nm_entry(new_nm, new_nm->file_ptr);
		 		//nm_sort();
		 		nm_print(new_nm);
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
		if (munmap(new_nm->file_ptr, new_nm->file_stat.st_size) < 0)
		{
			ft_putendl("munmap error");
			return (-1);
		}
		i++;
	}
	return (0);
}