/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:50:44 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 11:26:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	write_error(t_data *data, char *msg)
{
	if (!data->argv0)
		data->argv0 = "ft_ls";
	write(2, data->argv0, ft_strlen(data->argv0));
	write(2, ": ", 2);
	if (msg)
		write(2, msg, ft_strlen(msg));
}

void	write2(char *msg)
{
	write(2, msg, ft_strlen(msg));
}
