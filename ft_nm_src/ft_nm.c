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

#include "../includes/ft_nm_otool.h"

/*
**	First logical parse if needed
*/

void		parse_args(int argc, char **argv)
{
	if (argc == 1)
	{
		argv[1] = ft_strdup("a.out");
		argv[2] = NULL;
	}
}

int			main(int argc, char **argv)
{
	t_nm	*nm_list;

	nm_list = NULL;
	parse_args(argc, argv);
	if (ft_nm(nm_list, argv, 1) != 0)
		return (-1);
	return (0);
}
