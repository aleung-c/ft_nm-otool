/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:46:30 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/26 17:46:34 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_nm_otool.h"

void	to_hex(char *buffer, size_t size, unsigned n)
{
	size_t		i;
	size_t		j;
	char		c;
	unsigned	digit;

	i = 0;
	while (i < size)
	{
		digit = n & 0xf;
		buffer[i] = digit < 10 ? digit + '0' : digit - 10 + 'a';
		n >>= 4;
		if (n == 0)
			break ;
		i++;
	}
	buffer[i + 1] = 0;
	j = 0;
	while (j < i / 2)
	{
		c = buffer[j];
		buffer[j] = buffer[i - j];
		buffer[i - j] = c;
		++j;
	}
}

t_nm	*add_new_nm_file_to_list(t_nm *nm_list, t_nm *new_nm)
{
	t_nm	*tmp;

	if (nm_list == NULL)
	{
		return (new_nm);
	}
	else
	{
		tmp = nm_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_nm;
		return (nm_list);
	}
	return (nm_list);
}

unsigned int swap32(unsigned int x)
{
	return	((x << 24) & 0xff000000 ) |
		((x <<  8) & 0x00ff0000 ) |
		((x >>  8) & 0x0000ff00 ) |
		((x >> 24) & 0x000000ff );
}

void	add_output_to_list(t_nm *nm, t_nm_output *new_output)
{
	t_nm_output			*tmp;

	if (nm->output_list == NULL)
		nm->output_list = new_output;
	else
	{
		// insert by alphabetical order;
		if (ft_strcmp(new_output->sym_str, nm->output_list->sym_str) < 0)
		{
			new_output->next = nm->output_list;
			nm->output_list = new_output;
			return ;
		}
		tmp = nm->output_list;
		while (tmp->next && ft_strcmp(new_output->sym_str ,tmp->next->sym_str) >= 0)
			tmp = tmp->next;
		if (tmp->next)
			new_output->next = tmp->next;
		else
			new_output->next = NULL;
		tmp->next = new_output;
	}
}

/*long int	ft_strtol(char *line)
{
	long int	ret;
	long int	*hexa;
	int			cmp;
	int			power;

	cmp = 0;
	power = 0;
	ret = 0;
	hexa = (long int*)malloc(sizeof(long int) * ft_strlen(line));
	while (line[cmp])
	{
		if (line[cmp] >= 'A' && line[cmp] <= 'F')
			hexa[cmp] = line[cmp] + 10 - 'A';
		else if (line[cmp] >= '0' && line[cmp] <= '9')
			hexa[cmp] = line[cmp] - '0';
		cmp++;
	}
	while (--cmp >= 0)
	{
		ret += hexa[cmp] * pow(16, power);
		power++;
	}
	free(hexa);
	return (ret);
}*/

int			str_to_int(char *val)
{
	int i;
	int ret;
	int multiple;

	i = 0;
	ret = 0;
	multiple = 1;
	while (val[i] && val[i] != 96 && val[i] != 10 && val[i] != 32)
		i++;
	i--;
	while (i != -1)
	{
		// printf("%d \n", val[i]);
		ret = (val[i] - '0') * multiple + ret;
		multiple *= 10;
		i--;
	}
	return (ret);
}

int 		count_nm_list_members(t_nm *nm_list)
{
	int		i;
	t_nm	*tmp;

	i = 0;
	tmp = nm_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int 		count_nm_outputs(t_nm *nm)
{
	int				i;
	t_nm_output		*tmp;

	i = 0;
	tmp = nm->output_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int 		check_is_nm_doublon(t_nm *new_nm, t_nm *nm_list)
{
	t_nm		*tmp;

	tmp = nm_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->str_label, new_nm->str_label) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}















