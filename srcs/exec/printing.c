/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 16:12:13 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	print_entries(t_data *data)
{
	t_dir	*tmp;

	tmp = data->dirs;
	while (tmp)
	{
		if (data->flags & FLAG_RR)
			ft_printf("%s:\n", tmp->path);
		// if (data->flags & FLAG_L)
		// 	print_entries_lines(tmp);
		// else
		// 	print_entries_columns(tmp);
		tmp = tmp->next;
	}
	return (0);
}
