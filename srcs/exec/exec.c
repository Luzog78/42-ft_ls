/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:02:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 14:14:08 by ysabik           ###   ########.fr       */
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

static void	update_new_list(int flags, t_dir **new_list, t_dir *dir)
{
	t_entry	*tmp;

	if (flags & FLAG_RR)
	{
		tmp = dir->entries;
		while (tmp)
		{
			if (tmp->type == 'd' && ft_strcmp(tmp->name, ".")
				&& ft_strcmp(tmp->name, ".."))
				dir_add(new_list, dir_new(ft_strdup(tmp->path)));
			tmp = tmp->next;
		}
	}
	dir_add(new_list, dir->next);
}

/**
 * Phases of the program:
 * 
 * 1. Extraction
 * 
 * 2. Normalization
 * 
 * 3. Sorting
 * 
 * 4. Printing
 */
int	exec(t_data *data)
{
	int		r;
	t_dir	*new_list;
	t_dir	*tmp;

	if (data->flags & FLAG_HELP)
	{
		print_help();
		return (0);
	}
	while (data->dirs) {
		new_list = NULL;
		r = analyse_dir(data, data->dirs);
		if (r)
			continue ;
		normalise_entries(data, data->dirs);
		sort_entries(data, data->dirs);
		update_new_list(data->flags, &new_list, data->dirs);
		print_entries(data, data->dirs, !!new_list);
		tmp = data->dirs;
		tmp->next = NULL;
		dir_free(tmp);
		data->dirs = new_list;
	}
	return (r);
}
