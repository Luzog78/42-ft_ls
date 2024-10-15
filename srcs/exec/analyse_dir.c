/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:49:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/15 08:55:47 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	_starts_with(char *str, char *prefix)
{
	while (*prefix)
	{
		if (*str != *prefix)
			return (FALSE);
		str++;
		prefix++;
	}
	return (TRUE);
}

static void	_check_for_extended_acl(t_dir *dir, t_entry *entry)
{
	char	*desc;
	char	*line;

	entry->acl = acl_get_file(entry->path, ACL_TYPE_ACCESS);
	if (!entry->acl)
		return ;
	desc = acl_to_text(entry->acl, NULL);
	if (!desc)
		return ;
	line = desc;
	while (*line && entry->extended_acl != '+')
	{
		if (!_starts_with(line, "user::") && !_starts_with(line, "group::")
			&& !_starts_with(line, "other::"))
			entry->extended_acl = '+';
		while (*line && *line != '\n')
			line++;
		if (*line == '\n')
			line++;
	}
	acl_free(desc);
	if (entry->extended_acl == '+' && !dir->contains_acl)
		dir->contains_acl = TRUE;
}

static void	_update_blocks(t_dir *dir, t_entry *entry)
{
	entry->blocks = entry->stat.st_blocks * entry->stat.st_blksize / 8192.0;
	dir->total_blocks += entry->blocks;
}

static t_entry	*_analyse_dirent(t_data *data, t_dir *dir, struct dirent *file)
{
	t_entry	*entry;

	entry = entry_new(dir->path, ft_strdup(file->d_name));
	if (!entry || lstat(entry->path, &entry->stat) == -1)
		return (entry_free(entry), NULL);
	entry->type = analysis_get_type(entry->stat.st_mode);
	analysis_get_rights(entry->rights, entry->stat.st_mode);
	_check_for_extended_acl(dir, entry);
	entry->nlink = entry->stat.st_nlink;
	entry->owner = analysis_get_owner(entry->stat.st_uid);
	entry->group = analysis_get_group(entry->stat.st_gid);
	entry->size = entry->stat.st_size;
	if (data->flags & FLAG_U)
		entry->date = get_time(&entry->stat.st_atime);
	else
		entry->date = get_time(&entry->stat.st_mtime);
	if (entry->type == 'c' || entry->type == 'b')
	{
		entry->major = major(entry->stat.st_rdev);
		entry->size = minor(entry->stat.st_rdev);
	}
	if (entry->type == 'l')
		entry->linked_to = analysis_get_linked_to(entry->path);
	_update_blocks(dir, entry);
	return (dir->total_files++, entry);
}

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
		entry_add(&dir->entries, _analyse_dirent(data, dir, file));
	}
	closedir(dir->dir);
	return (0);
}
