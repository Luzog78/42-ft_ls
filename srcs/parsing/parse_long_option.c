/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_long_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:25:05 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 16:13:47 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @param	option 	String from argv, STARTING WITH '--' (so at least 3 bytes)
 * 
 * @return	int 	0 if success, 1 if minor problems, 2 if serious trouble
 */
int	parse_long_option(t_data *data, char *option)
{
	int	flag;

	if (!option[2])
		return (0);
	flag = get_s_flag(option);
	if (!flag)
	{
		write_error(data, "unrecognized option '");
		write2(option);
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
	return (0);
}
