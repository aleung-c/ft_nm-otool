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

#include "../includes/ft_nm_otool.h"
#include <stdio.h> //

// TODO : must display 000 hex add for the first elem...
void	handle_ar(t_nm *nm, char *file_ptr)
{
	struct ar_hdr		*ar_header;
	char 				*name;
	int					ar_size;
	int 				offset_size;
	struct ranlib		*ran_lib;
	unsigned int 		total_size_of_hdrs;

	uint32_t 			i;
	unsigned int y; //
	t_nm				*ar_child;

	i = 0;
	nm->is_ar = 1;
	nm->ar_childs = NULL;
	ar_header = (void *)file_ptr + SARMAG;
	name = (char *)ar_header + sizeof(struct ar_hdr);

	offset_size = str_to_int((void *)ar_header + 3);
	ran_lib = (void *)name + offset_size;
	total_size_of_hdrs = *(uint32_t *)((void *)ar_header + sizeof(struct ar_hdr) + offset_size);
	/*ft_putstr("total size of headers = ");
	ft_putnbr(total_size_of_hdrs);
	ft_putchar('\n');*/
	
	// move by one;
	ar_size = str_to_int(ar_header->ar_size);
	ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
	//i ++;
	y = 0;
	while (i < (total_size_of_hdrs / sizeof(struct ranlib))
		&& *((char *)ar_header) == '#') // semble OK.
	{
		name = (char *)ar_header + sizeof(struct ar_hdr);
		
		/*ft_putstr(nm->str_label);
		ft_putstr("(");
		ft_putstr(name);
		ft_putstr(")");
		ft_putstr(":\n");*/

		// print size of ar member;
		/*ft_putstr(" size = ");

		ft_putnbr(ar_size);*/
		ar_size = str_to_int(ar_header->ar_size);

		ar_child = (t_nm *)malloc(sizeof(t_nm));
		ar_child->str_label = ft_strdup(name);
		ar_child->ar_name = ft_strdup(nm->str_label);
		ar_child->is_ar = 0;
		ar_child->is_ar_member = 1;
		ar_child->next = NULL;
		offset_size = str_to_int((void *)ar_header + 3);
		/*ft_putstr("offset = ");
		ft_putnbr(offset_size);
		ft_putchar('\n');*/
		ar_child->file_ptr = (void *)ar_header + sizeof(*ar_header) + offset_size;

		// add it to output if doesnt already exist;
		if (check_is_nm_doublon(ar_child, nm->ar_childs) == 0)
		{
			nm->ar_childs = add_new_nm_file_to_list(nm->ar_childs, ar_child);
			nm_entry(ar_child, ar_child->file_ptr);
			//nm_print(ar_child);
			//ft_putchar('\n');
			y++;
		}
		else
		{
			free(ar_child->str_label);
			free(ar_child);
		}
		ar_header = (void *)ar_header + sizeof(*ar_header) + ar_size;
		i++;
		
	}

	/*ft_putstr("Nb of members in ar = ");
	ft_putnbr(y);
	ft_putchar('\n');*/
}
