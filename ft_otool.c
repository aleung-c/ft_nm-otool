#include "ft_nm_otool.h"

int		main(int argc, char **argv)
{
	t_nm	*nm_list;

	nm_list = NULL;
	parse_args(argc, argv);
	if (try_file_description(nm_list, argv) != 0)
		return (-1);
	return (0);
}
