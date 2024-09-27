/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:04:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/09/27 15:23:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @return int 	0 if success
 */
int	parse(t_data *data, int argc, char **argv)
{
	int	i;
	int	r;

	i = 1;
	r = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '-' && argv[i][2])
				r = parse_long_option(data, argv[i] + 2);
			else if (argv[i][1])
				r = parse_short_options(data, argv[i] + 1);
			else
				strlst_add(&data->path, strlst_new(ft_strdup(argv[i])));
			if (r)
				return (r);
		} else
			strlst_add(&data->path, strlst_new(ft_strdup(argv[i])));
		i++;
	}
	return (0);
}
