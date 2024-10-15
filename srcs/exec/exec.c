/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:02:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/15 09:52:03 by ysabik           ###   ########.fr       */
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

static void	exec_dir(t_data *data, t_dir **new_list, int r, int *res)
{
	if (r)
	{
		if (r > *res)
			*res = r;
		update_new_list(data->flags, new_list, data->dirs);
		return ;
	}
	normalise_entries(data, data->dirs);
	sort_entries(data, data->dirs);
	update_new_list(data->flags, new_list, data->dirs);
	if (data->is_tty)
		ft_printf("\r%*c\r", data->ws_col, ' ');
	print_entries(data, data->dirs, !!*new_list);
}

static void	_print_analysis(t_data *data)
{
	size_t	len;

	len = ft_strlen(data->dirs->path);
	if (len <= (size_t) data->ws_col - 17)
		ft_printf("%sAnalysis of '%s%s%s'...%s", COLR_FAINT, COLR_RESET,
			data->dirs->path, COLR_FAINT, COLR_RESET);
	else
		ft_printf("%sAnalysis of '...%s%s%s'...%s", COLR_FAINT, COLR_RESET,
			data->dirs->path + len - data->ws_col + 21, COLR_FAINT, COLR_RESET);
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
	int		res;
	t_dir	*new_list;
	t_dir	*tmp;

	if (data->flags & FLAG_HELP)
		return (print_help(), 0);
	res = 0;
	if (data->dirs && !data->dirs->path)
		exec_alone_files(data);
	while (data->dirs)
	{
		new_list = NULL;
		if (data->is_tty)
			_print_analysis(data);
		r = analyse_dir(data, data->dirs);
		exec_dir(data, &new_list, r, &res);
		tmp = data->dirs;
		tmp->next = NULL;
		dir_free(tmp);
		data->dirs = new_list;
	}
	return (res);
}
