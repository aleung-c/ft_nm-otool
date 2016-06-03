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

#include <stdint.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/cdefs.h>
#include <ar.h>


#include <mach-o/loader.h>				
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <mach-o/ranlib.h>
#include <mach/machine.h>
#include <architecture/byte_order.h>



typedef struct			s_nm_output
{
	int					arch_type;
	long				sym_value;
	char				sym_output[16];
	char				sym_type;
	char 				*sym_str;
	struct s_nm_output	*next;
}						t_nm_output;

typedef struct			s_nm
{
	char				*str_label;
	int 				is_ar_member;
	int					fd;
	struct stat			file_stat;
	char				*file_ptr;
	int					file_type;

	struct s_nm_output	*output_list;
	struct s_nm			*next;

	int					is_ar;
	int 				is_fat;
	int					is_dyld;
	char				*ar_name;
	struct s_nm			*ar_childs;
}						t_nm;

/*
** Function prototypes
*/

/*
**	Entry
*/
int						main(int argc, char **argv);

/*
**	Parser
*/
void					parse_args(int argc, char **argv);

/*
**	Nm functions
*/
int						try_file_description(t_nm *nm, char **argv);

void					nm_entry(t_nm *nm, char *file_ptr);

void					handle_64(t_nm *nm, char *file_ptr);
void					fill_outputs_64(t_nm *nm, int nsyms, int symoff, int stroff, char *file_ptr);
char					get_symbol_section_type_64(int section_nb, char *file_ptr);

void					handle_32(t_nm *nm, char *file_ptr);
void					fill_outputs_32(t_nm *nm, int nsyms, int symoff, int stroff, char *file_ptr);
char					get_symbol_section_type_32(int section_nb, char *file_ptr);

void					handle_fat(t_nm *nm, char *file_ptr);
void					handle_fat_cigam(t_nm *nm, char *file_ptr);

void					handle_ar(t_nm *nm, char *file_ptr);

void					add_output_to_list(t_nm *nm, t_nm_output *new_output);

void					nm_sort(t_nm *nm);

/*
** Display
*/
void					nm_print_from_list(t_nm *nm_list, int i);
void					nm_print(t_nm	*nm);
void					print_value_or_not(t_nm_output *tmp, t_nm *nm);
char					*clean_name(char *raw_name, int ext);
void					print_sym_value(t_nm_output *tmp);

/*
** Utils
*/
void					to_hex(char *buffer, size_t size, unsigned n);
void					print_format_hex_address(char *buffer, size_t size, long n);
t_nm					*add_new_nm_file_to_list(t_nm *nm_list, t_nm *new_nm);
unsigned int			swap32(unsigned int x);
//long int				ft_strtol(char *line);
int						str_to_int(char *val);
int		nm_search_64(char *file_ptr);

/*
** Utils symbols
*/
int						is_exceptional_global_symbol(t_nm *nm, char sym_type, char *sym_str);

/*
**	Utils Lists
*/
int						count_nm_list_members(t_nm *nm_list);
int						count_nm_outputs(t_nm *nm);
int						check_is_nm_doublon(t_nm *new_nm, t_nm *nm_list);

#endif