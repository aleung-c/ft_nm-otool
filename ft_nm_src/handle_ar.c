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

void		handle_ar(t_nm *nm, char *file_ptr)
{
	t_nm				*ar_child;
	t_ar_handler		a;
	unsigned int		i;
	unsigned int		ranlib_nb;

	nm->is_ar = 1;
	nm->ar_childs = NULL;
	i = 0;
	init_ar_handler(&a, file_ptr);
	ranlib_nb = a.total_size_of_hdrs / sizeof(struct ranlib);
	while (i < ranlib_nb && *((char *)a.ar_header) == '#')
	{
		a.name = (char *)a.ar_header + sizeof(struct ar_hdr);
		a.ar_size = str_to_int(a.ar_header->ar_size);
		ar_child = handle_ar_child(nm, &a);
		if (check_is_nm_doublon(ar_child, nm->ar_childs) == 0)
		{
			nm->ar_childs = add_new_nm_file_to_list(nm->ar_childs, ar_child);
			nm_entry(ar_child, ar_child->file_ptr);
		}
		else
			free_unused_child(ar_child);
		a.ar_header = (void *)a.ar_header + sizeof(*a.ar_header) + a.ar_size;
		i++;
	}
}

void		init_ar_handler(t_ar_handler *a, char *file_ptr)
{
	a->ar_header = (void *)file_ptr + SARMAG;
	a->name = (char *)a->ar_header + sizeof(struct ar_hdr);
	a->offset_size = str_to_int((void *)a->ar_header + 3);
	a->ran_lib = (void *)a->name + a->offset_size;
	a->total_size_of_hdrs = *(uint32_t *)((void *)a->ar_header
							+ sizeof(struct ar_hdr) + a->offset_size);
	a->ar_size = str_to_int(a->ar_header->ar_size);
	a->ar_header = (void *)a->ar_header + sizeof(*a->ar_header) + a->ar_size;
}

t_nm		*handle_ar_child(t_nm *nm, t_ar_handler *a)
{
	t_nm				*ar_child;

	ar_child = (t_nm *)malloc(sizeof(t_nm));
	ar_child->str_label = ft_strdup(a->name);
	ar_child->ar_name = ft_strdup(nm->str_label);
	ar_child->is_ar = 0;
	ar_child->is_ar_member = 1;
	ar_child->next = NULL;
	a->offset_size = str_to_int((void *)a->ar_header + 3);
	ar_child->file_ptr = (void *)a->ar_header + sizeof(*a->ar_header)
						+ a->offset_size;
	return (ar_child);
}
