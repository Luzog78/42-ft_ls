/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/06 15:38:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

# define MAX_LINE_LEN 100

static size_t	*_entries_len(t_dir *dir)
{
	t_entry	*tmp;
	size_t	*tab;
	size_t	i;

	tab = (size_t *) ft_malloc(dir->total_files * sizeof(size_t));
	if (!tab)
		return (NULL);
	tmp = dir->entries;
	i = 0;
	while (tmp)
	{
		tab[i] = ft_strlen(tmp->name);
		i++;
		tmp = tmp->next;
	}
	return (tab);
}

static char	**_names(t_dir *dir)
{
	t_entry	*tmp;
	char	**tab;
	size_t	i;

	tab = (char **) ft_malloc(dir->total_files * sizeof(char *));
	if (!tab)
		return (NULL);
	tmp = dir->entries;
	i = 0;
	while (tmp)
	{
		tab[i] = tmp->name;
		i++;
		tmp = tmp->next;
	}
	return (tab);
}

static size_t	*_columns_pattern(t_dir *dir)
{
	size_t	*columns;
	size_t	line_len;
	size_t	nb;
	size_t	rows;
	size_t	*entries_len;

	entries_len = _entries_len(dir);
	columns = NULL;
	nb = MAX_COLUMNS;
	while (nb > 1)
	{
		free(columns);
		line_len = 0;
		columns = (size_t *) ft_malloc((nb + 2) * sizeof(size_t));
		if (!columns)
			break ;
		rows = dir->total_files / nb;
		if (rows != (double) dir->total_files / nb)
			rows++;
		size_t i = 0;
		while (i < nb && i * rows < dir->total_files)
		{
			size_t max_len = 0;
			size_t j = 0;
			while (j < rows && i * rows + j < dir->total_files)
			{
				size_t len = entries_len[i * rows + j];
				if (len > max_len)
					max_len = len;
				j++;
			}
			line_len += max_len;
			columns[i + 2] = max_len;
			if (line_len > MAX_LINE_LEN - 2 * i)
				break ;
			i++;
		}
		columns[0] = i;
		columns[1] = rows;
		if (i == nb)
			break ;
		nb--;
	}
	return (free(entries_len), columns);
}

int	print_entries_columns(t_data *data, t_dir *dir)
{
	char	**names;
	size_t	*columns;
	size_t	i;
	size_t	j;

	(void)data;
	names = _names(dir);
	columns = _columns_pattern(dir);
	if (!names || !columns)
		return (free(names), free(columns), 2);
	j = 0;
	while (j < columns[1])
	{
		i = 0;
		while (i < columns[0])
		{
			if (i)
				write(1, "  ", 2);
			if (i * columns[1] + j < dir->total_files)
				ft_printf("%-*s", columns[i + 2], names[i * columns[1] + j]);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
	return (free(names), free(columns), 0);
}

int	print_entries(t_data *data, t_dir *dir, t_bool has_next)
{
	int	r;

	if (data->dir_title)
		ft_printf("%s:\n", dir->name);
	if (data->flags & FLAG_CC)
		r = print_entries_columns(data, dir);
	else
		r = print_entries_lines(data, dir);
	if (has_next)
		write(1, "\n", 1);
	return (r);
}
