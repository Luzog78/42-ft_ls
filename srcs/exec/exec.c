/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:02:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 12:09:54 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_help(void)
{
	int	i;

	ft_printf("Usage: ft_ls [OPTION]... [FILE]...\n\nOptions are:\n");
	i = 0;
	while (i < FLAGS_COUNT)
	{
		if (g_c_flags[i])
			ft_printf("  -%c", g_c_flags[i]);
		else
			ft_printf("    ");
		if (g_s_flags[i])
			ft_printf("  %-14s", g_s_flags[i]);
		else
			ft_printf("  %-14s", "");
		if (g_flags[i])
			ft_printf("  %s\n", g_desc_flags[i]);
		i++;
	}
	ft_printf("\nExit status:\n 0  if OK,\n");
	ft_printf(" 1  if minor problems (e.g., cannot access subdirectory),\n");
	ft_printf(
		" 2  if serious trouble (e.g., cannot access command-line argument).\n"
		);
}

int	exec(t_data *data)
{
	int	r;

	if (data->flags & FLAG_HELP)
	{
		print_help();
		return (0);
	}
	r = fill_entries(data);
	if (!r)
		r = print_entries(data);
	return (r);
}
