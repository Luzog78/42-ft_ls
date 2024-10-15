/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_alone_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:52:28 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/15 10:40:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	_err(t_data *data, t_entry *previous, t_entry **tmp)
{
	write2("ft_ls: cannot access '");
	write2((*tmp)->path);
	write2("'\n");
	if (previous)
		previous->next = (*tmp)->next;
	else
		data->dirs->entries = (*tmp)->next;
	(*tmp)->next = NULL;
	entry_free(*tmp);
	if (previous)
		*tmp = previous->next;
	else
		*tmp = data->dirs->entries;
}

void	exec_alone_files(t_data *data)
{
	t_entry	*previous;
	t_entry	*tmp;
	t_entry	*result;

	previous = NULL;
	tmp = data->dirs->entries;
	while (tmp)
	{
		result = analyse_file(data, NULL, tmp, tmp->path);
		if (!result)
		{
			_err(data, previous, &tmp);
			continue ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
	normalise_entries(data, data->dirs);
	sort_entries(data, data->dirs);
	print_entries(data, data->dirs, !!data->dirs->next);
	data->dirs = data->dirs->next;
}
