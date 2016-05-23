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

int	try_file_description(char **argv)
{
	int				fd;
	struct stat		file_stat;
	char			*file_ptr;

	// faire boucle des args;

	// open try;
	fd = open(argv[1], O_RDONLY);
	if (fd > 0)
	{
		fstat(fd, &file_stat);
	 	if ((file_ptr = mmap(0, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) != MAP_FAILED)
	 	{
	 		ft_putendl("File seems OK");
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
	if (munmap(file_ptr, file_stat.st_size) < 0)
	{
		ft_putendl("munmap error");
		return (-1);
	}
	return (0);
}

int		parse_args(char **argv)
{
	if (argv)
	{}
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc > 1 && (parse_args(argv)) == 0)
	{
		if (try_file_description(argv) != 0)
			return (-1);

	}
	else
	{
		ft_putendl("no args.");
	}
	return (0);
}