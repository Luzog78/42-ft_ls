/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries_columns.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:22:16 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/11 11:10:31 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_entry	*_entries(t_dir *dir)
{
	t_entry	*tmp;
	t_entry	*tab;
	size_t	i;

	tab = (t_entry *) ft_malloc((dir->total_files + 1) * sizeof(t_entry));
	if (!tab)
		return (NULL);
	tmp = dir->entries;
	i = 0;
	while (tmp)
	{
		tab[i] = *tmp;
		i++;
		tmp = tmp->next;
	}
	return (tab);
}

static void	_print_entry(size_t col_width, t_entry entry)
{
	if (entry.color)
		ft_printf("%s%-*s%s", entry.color,
			col_width + entry.name_len - entry.undiacritized_len,
			entry.name, COLR_RESET);
	else
		ft_printf("%-*s",
			col_width + entry.name_len - entry.undiacritized_len, entry.name);
}

int	print_entries_columns(t_data *data, t_dir *dir)
{
	t_entry	*entries;
	size_t	*columns;
	size_t	i;
	size_t	j;

	entries = _entries(dir);
	columns = columns_pattern(dir, !data->is_tty * NOTTY_COLS + data->ws_col);
	if (!entries || !columns)
		return (free(entries), free(columns), 2);
	j = 0;
	while (j < columns[1])
	{
		i = 0;
		while (i < columns[0])
		{
			if (i)
				write(1, "  ", 2);
			if (i * columns[1] + j < dir->total_files)
				_print_entry(columns[i + 2], entries[i * columns[1] + j]);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
	return (free(entries), free(columns), 0);
}
