/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 14:15:38 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/03 14:15:41 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

/// Unused in the end.
int		is_exceptional_global_symbol(t_nm *nm, char sym_type, char *sym_str)
{
	if (sym_type == 's')
	{
		if (ft_strstr(sym_str, "get_pc_thunk.bx"))
			return (1);
		else if (ft_strcmp(sym_str, "l_objc_msgSend_fixup_alloc") == 0)
			return (1);
		else if (ft_strcmp(sym_str, "l_objc_msgSend_fixup_release") == 0)
			return (1);
		else if (ft_strcmp(sym_str, "dyld_stub_binding_helper") == 0)
			return (1);
		else if (ft_strcmp(sym_str, "_dyld_lazy_dylib_path_fix") == 0)
			return (1);
		else if (ft_strcmp(sym_str, "_dyld_lazy_dylib_proxy") == 0)
			return (1);
	}
	if (sym_type == 't')
	{
		if (nm->is_dyld == 0 && (ft_strcmp(sym_str, "__dyld_func_lookup") == 0))
			return (1);
		else if (ft_strcmp(sym_str, "dyld_stub_binding_helper") == 0)
			return (1); 
		else if (ft_strcmp(sym_str, "__start") == 0)
			return (1);
		else if (ft_strcmp(sym_str, "_lazy_load_dylib") == 0)
			return (1);
		else if (ft_strcmp(sym_str, "dyld_lazy_dylib_stub_binding_helper") == 0)
			return (1);
	}
	return (0);
}
