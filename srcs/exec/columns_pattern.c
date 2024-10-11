/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:23:27 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/11 11:24:44 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static size_t	_try_filling(t_dir *dir, size_t max_line_len, t_pattern *p)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	max_len;

	i = 0;
	while (i < p->nb && i * p->rows < dir->total_files)
	{
		max_len = 0;
		j = 0;
		while (j < p->rows && i * p->rows + j < dir->total_files)
		{
			len = p->entries_len[i * p->rows + j++];
			if (len > max_len)
				max_len = len;
		}
		p->line_len += max_len;
		p->columns[i + 2] = max_len;
		if (p->line_len > max_line_len - 2 * i)
			break ;
		i++;
	}
	p->columns[0] = i;
	p->columns[1] = p->rows;
	return (i);
}

static size_t	*_single_column(t_dir *dir)
{
	size_t	*columns;
	size_t	len;
	size_t	i;

	columns = (size_t *) ft_malloc(3 * sizeof(size_t));
	if (!columns)
		return (NULL);
	columns[0] = 1;
	columns[1] = dir->total_files;
	columns[2] = 0;
	i = 0;
	while (i < dir->total_files)
	{
		len = ft_strlen(dir->entries->name);
		if (len > columns[2])
			columns[2] = len;
		i++;
	}
	return (columns);
}

size_t	*columns_pattern(t_dir *dir, size_t max_line_len)
{
	t_pattern	p;

	p.entries_len = _entries_len(dir);
	p.columns = NULL;
	p.nb = max_line_len / 3;
	while (p.nb > 1)
	{
		free(p.columns);
		p.line_len = 0;
		p.columns = (size_t *) ft_malloc((p.nb + 2) * sizeof(size_t));
		if (!p.columns)
			break ;
		p.rows = dir->total_files / p.nb;
		if (p.rows != (double) dir->total_files / p.nb)
			p.rows++;
		if (_try_filling(dir, max_line_len, &p) == p.nb)
			break ;
		p.nb--;
	}
	if (p.columns == NULL)
		return (free(p.entries_len), _single_column(dir));
	return (free(p.entries_len), p.columns);
}
