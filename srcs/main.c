/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 17:17:09 by ysabik           ###   ########.fr       */
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
	data.path = NULL;
	data.dirs = NULL;
	r = parse(&data, argc, argv);
	data.dir_title = (data.path && data.path->next) || data.flags & FLAG_RR;
	ft_printf("flags: %d | ", data.flags);
	for (int i = 0; i < FLAGS_COUNT; i++)
	{
		if (data.flags & g_flags[i])
		{
			if (g_c_flags[i])
				ft_printf("%c ", g_c_flags[i]);
			else
				ft_printf("%s ", g_s_flags[i]);
		}
	}
	ft_printf("\nSorting method: %d\n", data.sort);
	for (t_strlst *tmp = data.path; tmp; tmp = tmp->next)
		ft_printf("path: %s\n", tmp->str);
	if (!r)
		r = exec(&data);
	strlst_free(data.path);
	dir_free(data.dirs);
	return (r);
}
