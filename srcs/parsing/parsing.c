/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:04:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/15 10:44:36 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_not_dir(t_data *data, t_dir *alone_files,
	t_dir *previous, t_dir **tmp)
{
	entry_add(&alone_files->entries,
		entry_new(ft_strdup((*tmp)->path), ft_strdup((*tmp)->path)));
	if (previous)
		previous->next = (*tmp)->next;
	else
		data->dirs = (*tmp)->next;
	(*tmp)->next = NULL;
	dir_free(*tmp);
	if (previous)
		*tmp = previous->next;
	else
		*tmp = data->dirs;
}

static void	_insert_alone_files(t_data *data, t_dir *alone_files)
{
	if (alone_files->entries)
	{
		alone_files->next = data->dirs;
		data->dirs = alone_files;
	}
	else
		dir_free(alone_files);
}

static void	_dissociate_files_dirs(t_data *data)
{
	t_dir	*alone_files;
	t_dir	*previous;
	t_dir	*tmp;
	DIR		*dir;

	alone_files = dir_new("");
	if (!alone_files)
		return ;
	alone_files->path = NULL;
	previous = NULL;
	tmp = data->dirs;
	while (tmp)
	{
		dir = opendir(tmp->path);
		if (!dir || data->flags & FLAG_D)
		{
			_not_dir(data, alone_files, previous, &tmp);
			closedir(dir);
			continue ;
		}
		closedir(dir);
		previous = tmp;
		tmp = tmp->next;
	}
	_insert_alone_files(data, alone_files);
}

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
	return (_dissociate_files_dirs(data), r);
}
