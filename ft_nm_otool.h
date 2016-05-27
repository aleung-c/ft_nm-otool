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



typedef struct			s_nm_output
{
	int					sym_value;
	char				sym_output[16];
	char				sym_type;
	char 				*sym_str;
	struct s_nm_output	*next;
}						t_nm_output;

typedef struct			s_nm
{
	int					fd;
	struct stat			file_stat;
	char				*file_ptr;
	int					is_fat_bin;
	int					is_reverse_fat_bin;
	struct s_nm			*fat_childs;

	struct s_nm_output	*output_list;
	struct s_nm			*next;
}						t_nm;

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
void		parse_args(int argc, char **argv);

/*
**	Nm functions
*/
int		try_file_description(t_nm *nm, char **argv);

void	nm_entry(t_nm *nm, char *file_ptr);

void	handle_64(t_nm *nm, char *file_ptr);
void	fill_outputs_64(t_nm *nm, int nsyms, int symoff, int stroff);

void	handle_fat(t_nm *nm, char *file_ptr);

void	add_output_to_list(t_nm *nm, t_nm_output *new_output);
void	nm_print(t_nm	*nm);

/*
** Utils
*/
void	to_hex(char *buffer, size_t size, unsigned n);
void	print_format_hex_address(char *output);
t_nm	*add_new_nm_file_to_list(t_nm *nm_list, t_nm *new_nm);
unsigned int swap32(unsigned int x);

#endif