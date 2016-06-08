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

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# include "../libft/libft.h"

# include <stdint.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/cdefs.h>
# include <ar.h>

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <mach/machine.h>
# include <architecture/byte_order.h>

typedef struct					s_nm_output
{
	long						sym_value;
	char						sym_output[16];
	char						sym_type;
	char						*sym_str;
	struct s_nm_output			*next;
}								t_nm_output;

typedef struct					s_ot_output
{
	long						sect_addr;
	char						seg_name[16];
	char						sect_name[16];
	unsigned int				sect_size;
	char						*sect_mem;
	struct s_ot_output			*next;
}								t_ot_output;

/*
** t_nm struct represent a file, not caring if its
** for nm or otool.
*/

typedef struct					s_nm
{
	int							arch_type;
	char						*str_label;

	int							fd;
	struct stat					file_stat;
	char						*file_ptr;
	int							file_type;

	struct s_nm_output			*output_list;
	struct s_ot_output			*ot_output_list;

	int							is_err;
	int							is_ar;
	int							is_ar_member;
	int							is_fat;
	int							is_dyld;
	char						*ar_name;
	struct s_nm					*ar_childs;

	struct s_nm					*next;
}								t_nm;

typedef struct					s_ar_handler
{
	struct ar_hdr				*ar_header;
	char						*name;
	int							ar_size;
	int							offset_size;
	struct ranlib				*ran_lib;
	unsigned int				total_size_of_hdrs;
	uint32_t					i;
}								t_ar_handler;

typedef struct					s_bin32_handler
{
	struct mach_header			*file_header;
	struct load_command			*lc;
	struct segment_command		*sc;
	int							ncmds;

	struct symtab_command		*symtab;
	int							nsyms;
	int							symoff;
	int							stroff;

	struct nlist				*list;
	struct section				*sect;
	int							section_counter;
}								t_bin32_handler;

typedef struct					s_bin64_handler
{
	struct mach_header_64		*file_header;
	struct load_command			*lc;
	struct segment_command_64	*sc;
	int							ncmds;

	struct symtab_command		*symtab;
	int							nsyms;
	int							symoff;
	int							stroff;

	struct nlist_64				*list;
	struct section_64			*sect;
	int							section_counter;
}								t_bin64_handler;

typedef struct					s_fatbin_handler
{
	struct fat_header			*fat_head;
	struct fat_arch				*fat_arch_struct;
	unsigned int				magic_number;

	struct ar_hdr				*ar_header;
	unsigned int				ar_size;
	unsigned int				offset_size;
	char						*sent_file_ptr;
}								t_fatbin_handler;

/*
** Function prototypes
*/

/*
**	Entry
*/
int								main(int argc, char **argv);

/*
**	Parser
*/
void							parse_args(int argc, char **argv);

/*
**	Nm functions
*/
int								ft_nm(t_nm *nm_list, char **argv, int i);
t_nm							*create_new_nm(char **argv, int i);
void							print_error(char **argv, int i, int error_type);

void							nm_entry(t_nm *nm, char *file_ptr);

void							handle_64(t_nm *nm, char *file_ptr);
void							fill_outputs_64(t_nm *nm, t_bin64_handler *b,
										char *file_ptr);
char							get_symbol_type_64(t_bin64_handler *b,
													char *file_ptr, int i);
char							get_symbol_section_type_64(t_bin64_handler *b,
											int section_nb, char *file_ptr);
char							get_symbol_type_sectioncmp_64(t_bin64_handler
											*b, int section_nb);

void							handle_32(t_nm *nm, char *file_ptr);
void							fill_outputs_32(t_nm *nm, t_bin32_handler *b,
											char *file_ptr);
char							get_symbol_type_32(t_bin32_handler *b,
											char *file_ptr, int i);
char							get_symbol_section_type_32(t_bin32_handler *b,
											int section_nb, char *file_ptr);
char							get_symbol_type_sectioncmp_32(t_bin32_handler
											*b, int section_nb);

void							handle_fat(t_nm *nm, char *file_ptr);
void							handle_fat_cigam(t_nm *nm, char *file_ptr);
int								search_for_64_arch(t_fatbin_handler *b,
										char *sent_file_ptr, char *file_ptr);
int								search_for_64_arch_cigam(t_fatbin_handler *b,
										char *sent_file_ptr, char *file_ptr);
void							*get_valid_arch(t_fatbin_handler *b,
												char *file_ptr);
void							*get_valid_arch_cigam(t_fatbin_handler *b,
												char *file_ptr);

void							handle_ar(t_nm *nm, char *file_ptr);
void							init_ar_handler(t_ar_handler *a,
										char *file_ptr);
t_nm							*handle_ar_child(t_nm *nm, t_ar_handler *a);

void							add_output_to_list(t_nm *nm,
												t_nm_output *new_output);

void							nm_sort(t_nm *nm);

/*
**	Otool functions
*/

int								ft_otool(t_nm *nm_list, char **argv, int i);

void							otool_entry(t_nm *nm, char *file_ptr);

void							handle_32_otool(t_nm *nm, char *file_ptr);
void							handle_32_regular_object(t_nm *nm,
										t_bin32_handler *b, char *file_ptr);
void							handle_32_regular_section_run(t_nm *nm,
										t_bin32_handler *b, char *file_ptr);
void							handle_32_mh_object(t_nm *nm,
										t_bin32_handler *b, char *file_ptr);
void							fill_ot_output_32(t_nm *nm,
									struct section *sect, char *ptr_to_text);

void							handle_64_otool(t_nm *nm, char *file_ptr);
void							handle_64_regular_object(t_nm *nm,
										t_bin64_handler *b, char *file_ptr);
void							handle_64_regular_section_run(t_nm *nm,
										t_bin64_handler *b, char *file_ptr);
void							handle_64_mh_object(t_nm *nm,
										t_bin64_handler *b, char *file_ptr);

void							fill_ot_output_64(t_nm *nm,
								struct section_64 *sect, char *ptr_to_text);

void							handle_fat_otool(t_nm *nm, char *file_ptr);
void							handle_fat_cigam_otool(t_nm *nm,
										char *file_ptr);

void							handle_ar_otool(t_nm *nm, char *file_ptr);
void							init_ar_handler_otool(t_ar_handler *a,
										char *file_ptr);
t_nm							*handle_ar_child_otool(t_nm *nm,
										t_ar_handler *a);

void							add_ot_output_to_list(t_nm *nm,
											t_ot_output *new_output);

/*
** Display
*/

void							nm_print_from_list(t_nm *nm_list, int i);
void							nm_print(t_nm	*nm);
void							nm_print_ar_label(t_nm *tmp);
void							print_value_or_not(t_nm_output *tmp, t_nm *nm);
char							*clean_name(char *raw_name, int ext);
void							print_sym_value(t_nm_output *tmp,
									int arch_type);

void							ot_print_from_list(t_nm *nm_list, int i);
void							ot_print(t_nm	*tmp);
void							print_file_name(t_nm *tmp);
void							ft_putnbytes(char *buffer, size_t size,
										unsigned int n);
void							print_ar_member_name(t_nm *tmp);
void							print_ot_addr_val(char *buffer, t_nm *nm,
									t_ot_output *tmp, int sect_size_counter);
void							print_section_bytes(char *buffer,
										char *ptr_to_text);

/*
** Utils
*/

void							to_hex(char *buffer, size_t size, unsigned n);
void							print_format_hex_address(char *buffer,
										size_t size, long n);
t_nm							*add_new_nm_file_to_list(t_nm *nm_list,
										t_nm *new_nm);
unsigned int					swap32(unsigned int x);
int								str_to_int(char *val);
int								nm_search_64(char *file_ptr);
int								is_magicn_handled(void *sent_ptr);

/*
** Utils symbols
*/
int								is_exceptional_global_symbol(t_nm *nm,
										char sym_type, char *sym_str);

/*
**	Utils Lists
*/
int								count_nm_list_members(t_nm *nm_list);
int								count_nm_outputs(t_nm *nm);
int								count_ot_outputs(t_nm *nm);
int								check_is_nm_doublon(t_nm *new_nm,
										t_nm *nm_list);
void							free_unused_child(t_nm *ar_child);

#endif
