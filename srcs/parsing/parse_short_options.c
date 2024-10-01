/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_short_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:25:26 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 16:13:39 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @return int 	0 if success, 1 if minor problems, 2 if serious trouble
 */
int	parse_short_options(t_data *data, char *options)
{
	char	c;
	int		flag;

	while (*options)
	{
		c = *options++;
		flag = get_c_flag(c);
		if (!flag)
		{
			write_error(data, "invalid option -- '");
			write2(&c);
			write2("'\nTry '");
			write2(data->argv0);
			write2(" --help' for more information.\n");
			return (2);
		}
		data->flags = or_flag(data->flags, flag);
		if (flag & FLAG_F && data->sort == DEFAULT_SORT)
			data->sort = DIR_SORT;
		if (flag & FLAG_T)
			data->sort = LAST_MODIF_SORT;
	}
	return (0);
}
