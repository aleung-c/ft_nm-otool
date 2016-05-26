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
#include <sys/cdefs.h>
#include <mach-o/loader.h>				
#include <mach-o/nlist.h>

#include <mach-o/fat.h>
#include <sys/stat.h>

#include <stdint.h>
#include <mach/machine.h>
#include <architecture/byte_order.h>

typedef struct		s_nm
{
	int				fd;
	struct stat		file_stat;
	char			*file_ptr;
}					t_nm;

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
int		try_file_description(t_nm *nm, char **argv);

void	handle_64bin(t_nm *nm, char *file_ptr);
void	print_symbols(struct load_command *lc, int nsyms,
						int symoff, int stroff, char *ptr);


/*
** Utils
*/
void	to_hex(char *buffer, size_t size, unsigned n);
void	print_format_hex_address(char *output);

#endif