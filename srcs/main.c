/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 15:37:53 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		r;

	data.argv0 = argv[0];
	data.flags = 0;
	data.sort = DEFAULT_SORT;
	data.dir_title = FALSE;
	data.dirs = NULL;
	r = parse(&data, argc, argv);
	data.dir_title = (data.dirs && data.dirs->next) || data.flags & FLAG_RR;
	if (!r)
		r = exec(&data);
	dir_free(data.dirs);
	return (r);
}
