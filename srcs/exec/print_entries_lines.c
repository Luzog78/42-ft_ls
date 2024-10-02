/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:05:16 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 11:26:29 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_line(t_data *data, t_dir *dir, t_entry *entry)
{
	if (data->flags & (FLAG_L | FLAG_G))
		ft_printf(dir->chmod_format, entry->type, entry->rights, entry->nlink);
	if (data->flags & FLAG_L)
		ft_printf(dir->owner_format, entry->owner);
	if (data->flags & (FLAG_L | FLAG_G))
	{
		ft_printf(dir->group_format, entry->group);
		if (entry->type == 'b' || entry->type == 'c')
			ft_printf(dir->major_format, entry->major);
		ft_printf(dir->size_format, entry->size);
	}
	write(1, entry->path, ft_strlen(entry->path));
	if (data->flags & (FLAG_L | FLAG_G) && entry->type == 'l')
		ft_printf(" -> %s", entry->linked_to);
}

int	print_entries_lines(t_data *data, t_dir *dir)
{
	t_entry	*tmp;

	tmp = dir->entries;
	while (tmp)
	{
		print_line(data, dir, tmp);
		if (data->flags & (FLAG_L | FLAG_G | FLAG_1) || !tmp->next)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		tmp = tmp->next;
	}
	return (0);
}
