/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/08 11:23:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
