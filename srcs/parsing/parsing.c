/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:04:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 11:59:47 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @return int 	0 if success, 1 if minor problems, 2 if serious trouble
 */
int	parse(t_data *data, int argc, char **argv)
{
	int	i;
	int	r;

	i = 1;
	r = 0;
	while (i < argc && !r)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '-')
				r = parse_long_option(data, argv[i]);
			else if (argv[i][1])
				r = parse_short_options(data, argv[i] + 1);
			else
				dir_add(&data->dirs, dir_new(ft_strdup(argv[i])));
		}
		else
			dir_add(&data->dirs, dir_new(ft_strdup(argv[i])));
		i++;
	}
	if (!r && !data->dirs)
		dir_add(&data->dirs, dir_new(ft_strdup(".")));
	if (data->flags & FLAG_U && data->flags & FLAG_T)
		data->sort = LAST_ACCESS_SORT;
	return (r);
}
