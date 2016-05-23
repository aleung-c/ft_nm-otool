/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 18:05:27 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/23 18:05:31 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef		FT_NM_OTOOL_H
# define	FT_NM_OTOOL_H

#include <stdio.h> //

#include "libft/libft.h"

#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>





/*
** Function prototypes
*/

/*
**	Entry
*/
int		main(int argc, char **argv);

/*
**	Parser
*/
int		parse_args(char **argv);

/*
**	Nm functions
*/
int		try_file_description(char **argv);

#endif