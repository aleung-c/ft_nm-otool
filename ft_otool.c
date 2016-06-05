#include "ft_nm_otool.h"

void	otool_entry(t_nm *nm, char *file_ptr)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)file_ptr;
	if (magic_number == MH_MAGIC)
	{
		// 32bit exec file;
		//ft_putendl("bin 32bit");
		handle_32(nm, file_ptr);
	}
	else if (magic_number == MH_MAGIC_64)
	{
		// 64bit exec file;
		//ft_putendl("bin 64bit");
		handle_64_otool(nm, file_ptr);
	}
	else if (magic_number == FAT_MAGIC)
	{
		// fat file.
		//ft_putendl("bin fat");
		handle_fat(nm, file_ptr);
	}
	else if (magic_number == FAT_CIGAM)
	{
		// fat file endian reversed.
		//ft_putendl("bin fat cigam");
		handle_fat_cigam(nm, file_ptr);
	}
	else if (ft_memcmp(file_ptr, ARMAG, SARMAG) == 0)
	{
		//ft_putendl("Lib");
		handle_ar(nm, file_ptr);
	}
}

int		main(int argc, char **argv)
{
	t_nm	*nm_list;

	nm_list = NULL;
	parse_args(argc, argv);
	if (try_file_description(nm_list, argv) != 0)
		return (-1);
	return (0);
}
