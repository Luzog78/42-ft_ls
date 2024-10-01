/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 17:05:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	print_entries(t_data *data, t_dir *dir, t_bool has_next)
{
	int		r;
	t_entry	*tmp;

	r = 0;
	if (data->dir_title)
		ft_printf("%s:\n", dir->path);
	tmp = dir->entries;
	while (tmp)
	{
		ft_printf("%s\n", tmp->path);
		tmp = tmp->next;
	}
	if (has_next)
		write(1, "\n", 1);
	return (r);
}
