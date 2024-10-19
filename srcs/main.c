/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/11 10:25:51 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	_default_flags(t_data *data)
{
	if (data->is_tty)
		data->flags |= FLAG_COLOR;
	if (!(data->flags & (FLAG_1 | FLAG_L | FLAG_G | FLAG_CC)))
	{
		if (data->is_tty)
			data->flags |= FLAG_CC;
		else
			data->flags |= FLAG_1;
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	int				r;
	struct winsize	w;

	data.ws_col = 0;
	data.ws_row = 0;
	data.is_tty = FALSE;
	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
	{
		data.ws_col = w.ws_col;
		data.ws_row = w.ws_row;
		data.is_tty = w.ws_col > 0;
	}
	data.argv0 = argv[0];
	data.flags = 0;
	data.sort = DEFAULT_SORT;
	data.dir_title = FALSE;
	data.dirs = NULL;
	r = parse(&data, argc, argv);
	data.dir_title = (data.dirs && data.dirs->next) || data.flags & FLAG_RR;
	_default_flags(&data);
	if (!r)
		r = exec(&data);
	return (dir_free(data.dirs), r);
}
