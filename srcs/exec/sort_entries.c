/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:44:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/08 15:18:41 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	_sort_method(t_entry *a, t_entry *b, t_sort sort, t_bool rev)
{
	t_bool	res;

	if (sort == LAST_MODIF_SORT && a->stat.st_mtime != b->stat.st_mtime)
		res = a->stat.st_mtime < b->stat.st_mtime;
	else if (sort == LAST_ACCESS_SORT && a->stat.st_atime != b->stat.st_atime)
		res = a->stat.st_atime < b->stat.st_atime;
	else
		res = undiacritics_sort(a->undiacritized, b->undiacritized) > 0;
	if (rev)
		return (!res);
	return (res);
}

static void	_sort(t_dir *dir, t_sort sort, t_bool reversed)
{
	t_entry	*tmp;
	t_entry	*prv;
	t_entry	*nxt;

	tmp = dir->entries;
	prv = NULL;
	while (tmp)
	{
		nxt = tmp->next;
		if (nxt && _sort_method(tmp, nxt, sort, reversed))
		{
			if (prv == NULL)
				dir->entries = nxt;
			else
				prv->next = nxt;
			tmp->next = nxt->next;
			nxt->next = tmp;
			prv = NULL;
			tmp = dir->entries;
			continue ;
		}
		prv = tmp;
		tmp = nxt;
	}
}

void	sort_entries(t_data *data, t_dir *dir)
{
	if (data->sort == DEFAULT_SORT || data->flags & FLAG_CC)
		undiacritize(dir);
	_sort(dir, data->sort, data->flags & FLAG_R);
}
