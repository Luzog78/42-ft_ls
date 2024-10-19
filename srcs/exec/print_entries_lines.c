/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:05:16 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/14 19:16:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	_print_name(t_entry *entry)
{
	if (entry->color)
		ft_printf("%s%s%s", entry->color, entry->name, COLR_RESET);
	else
		write(1, entry->name, ft_strlen(entry->name));
}

static void	print_line(t_data *data, t_dir *dir, t_entry *entry)
{
	if (data->flags & FLAG_S)
		ft_printf("%*lu ", dir->blocks_len, entry->blocks);
	if (data->flags & (FLAG_L | FLAG_G))
	{
		ft_printf("%c%s", entry->type, entry->rights);
		if (dir->contains_acl)
			ft_printf("%c", entry->extended_acl);
		ft_printf(" %*lu", dir->nlink_len, entry->nlink);
	}
	if (data->flags & FLAG_L)
		ft_printf(" %-*s", dir->owner_len, entry->owner);
	if (data->flags & (FLAG_L | FLAG_G))
	{
		ft_printf(" %-*s", dir->group_len, entry->group);
		if (entry->type == 'b' || entry->type == 'c')
			ft_printf(" %*lu, ", dir->major_len, entry->major);
		else if (dir->contains_block_char_files)
			ft_printf(" %*s", dir->major_len + 2, "");
		ft_printf(" %*lu %s ", dir->size_len, entry->size, entry->date);
	}
	_print_name(entry);
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
