/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:30:08 by ysabik            #+#    #+#             */
/*   Updated: 2024/09/27 15:25:03 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.flags = 0;
	data.path = NULL;
	data.dirs = NULL;
	parse(&data, argc, argv);
	strlst_free(data.path);
	dir_free(data.dirs);
	return (0);
}
