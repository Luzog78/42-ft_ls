/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_formats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:53:17 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 15:38:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	nbrlen(size_t n)
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

static void	update_field(size_t *field, size_t value)
{
	if (value > *field)
		*field = value;
}

static void	set_dir_len(t_data *data, t_dir *dir)
{
	t_entry	*tmp;

	tmp = dir->entries;
	while (tmp)
	{
		if (data->flags & (FLAG_L | FLAG_G))
		{
			update_field(&dir->nlink_len, nbrlen(tmp->nlink));
			update_field(&dir->major_len, nbrlen(tmp->major));
			update_field(&dir->size_len, nbrlen(tmp->size));
			update_field(&dir->owner_len, ft_strlen(tmp->owner));
			update_field(&dir->group_len, ft_strlen(tmp->group));
			update_field(&dir->date_len, ft_strlen(tmp->date));
		}
		else
			update_field(&dir->name_len, ft_strlen(tmp->name));
		tmp = tmp->next;
	}
}

static void	set_format(char **field, char *str, size_t offset, size_t len)
{
	*field = ft_strdup(str);
	if (!*field)
		return ;
	ulina(*field + offset, len);
}

void	set_dir_formats(t_data *data, t_dir *dir)
{
	set_dir_len(data, dir);
	set_format(&dir->chmod_format, "%c%s %          lu ", 16, dir->nlink_len);
	set_format(&dir->owner_format, "%-          s ", 12, dir->owner_len);
	set_format(&dir->group_format, "%-          s ", 12, dir->group_len);
	set_format(&dir->major_format, "%          lu, ", 11, dir->major_len);
	set_format(&dir->major_spacing, "% s", 2, dir->major_len + 2);
	set_format(&dir->size_format, "%          lu ", 11, dir->size_len);
	set_format(&dir->date_format, "%          s ", 11, dir->date_len);
	set_format(&dir->name_format, "%          s ", 11, dir->name_len);
}
