/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by ysabik            #+#    #+#             */
/*   Updated: 2024/09/30 17:44:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		r;

	data.argv0 = argv[0];
	data.flags = 0;
	data.path = NULL;
	data.dirs = NULL;
	r = parse(&data, argc, argv);
	ft_printf("flags: %d\n", data.flags);
	for (t_strlst *tmp = data.path; tmp; tmp = tmp->next)
		ft_printf("path: %s\n", tmp->str);
	strlst_free(data.path);
	dir_free(data.dirs);
	return (!!r);
}
