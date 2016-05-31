/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:06:25 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/31 15:06:32 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
#include <stdio.h> //

// TODO : must display 000 hex add for the first elem...
// + segfault sur certaines libs. check offsets.
void	handle_ar(t_nm *nm, char *file_ptr)
{
	struct ar_hdr		*ar_header;
	char 				*name;
	int					ar_size;
	struct ranlib		*ran_lib;
	unsigned int 		total_size_of_hdrs;
	uint32_t 			i;

	t_nm				*ar_child;

	i = 1;
	nm->is_ar = 1;
	nm->ar_childs = NULL;
	ar_header = (void *)file_ptr + SARMAG;
	name = (char *)ar_header + sizeof(struct ar_hdr);

	ran_lib = (void *)name + 20;
	total_size_of_hdrs = *(uint32_t *)((void *)ar_header + 20 + sizeof(struct ar_hdr));
	/*ft_putstr("total size of headers = ");
	ft_putnbr(total_size_of_hdrs);
	ft_putchar('\n');*/

	// move by one;
	ar_size = str_to_int(ar_header->ar_size);
	ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
	while (i < (total_size_of_hdrs / sizeof(struct ranlib)))
	{
		name = (char *)ar_header + sizeof(struct ar_hdr);
		
		ft_putnstr(name, 16);
		ft_putstr(" :\n");
		
		// print size of ar member;
		/*ft_putstr(" size = ");
		
		ft_putnbr(ar_size);*/
		ar_size = str_to_int(ar_header->ar_size);

		ar_child = (t_nm *)malloc(sizeof(t_nm));
		ar_child->is_ar_member = 1;
		ar_child->next = NULL;
		ar_child->file_ptr = (void *)ar_header + sizeof(*ar_header) + 20;
		nm->ar_childs = add_new_nm_file_to_list(nm->ar_childs, ar_child);
		nm_entry(ar_child, ar_child->file_ptr);
		nm_print(ar_child);
		ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
		i++;
	}
	//ft_putstr(" nb of members = ");
	//printf("%d\n", i);
	ft_putchar('\n');
}
