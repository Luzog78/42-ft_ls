/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:53:17 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/13 17:15:28 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	_nbrlen(size_t n)
{
	size_t	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	_update_field(size_t *field, size_t value)
{
	if (value > *field)
		*field = value;
}

void	set_dir_len(t_data *data, t_dir *dir)
{
	t_entry	*tmp;

	tmp = dir->entries;
	while (tmp)
	{
		if (data->flags & (FLAG_L | FLAG_G))
		{
			_update_field(&dir->nlink_len, _nbrlen(tmp->nlink));
			_update_field(&dir->major_len, _nbrlen(tmp->major));
			_update_field(&dir->size_len, _nbrlen(tmp->size));
			_update_field(&dir->owner_len, ft_strlen(tmp->owner));
			_update_field(&dir->group_len, ft_strlen(tmp->group));
			_update_field(&dir->date_len, ft_strlen(tmp->date));
		}
		else
		{
			tmp->name_len = ft_strlen(tmp->name);
			_update_field(&dir->name_len, tmp->name_len);
		}
		tmp = tmp->next;
	}
}
