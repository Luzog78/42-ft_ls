/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:49:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/15 10:00:26 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	analyse_dir(t_data *data, t_dir *dir)
{
	struct dirent	*file;

	dir->name = ft_strdup(dir->path);
	dir->dir = opendir(dir->path);
	if (!dir->dir)
	{
		write_error(data, "cannot access '");
		write2(dir->name);
		write2("'\n");
		return (1);
	}
	while (TRUE)
	{
		file = readdir(dir->dir);
		if (!file)
			break ;
		if ((file->d_name[0] == '.' && !(data->flags & (FLAG_AA | FLAG_A)))
			|| ((!ft_strcmp(file->d_name, ".")
					|| !ft_strcmp(file->d_name, ".."))
				&& !(data->flags & FLAG_A)))
			continue ;
		entry_add(&dir->entries, analyse_file(data, dir, NULL, file->d_name));
	}
	closedir(dir->dir);
	return (0);
}
