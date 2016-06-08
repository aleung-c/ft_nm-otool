/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:06:46 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/06 13:06:51 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm_otool.h"

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
	if (ft_otool(nm_list, argv, 1) != 0)
		return (-1);
	return (0);
}
