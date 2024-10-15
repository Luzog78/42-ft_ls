/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:52:57 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/15 10:44:58 by ysabik           ###   ########.fr       */
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
	if (dir && entry->extended_acl == '+' && !dir->contains_acl)
		dir->contains_acl = TRUE;
}

static void	_update_fields(t_data *data, t_dir *dir, t_entry *entry)
{
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
	entry->blocks = entry->stat.st_blocks * entry->stat.st_blksize / 8192.0;
	if (dir)
		dir->total_blocks += entry->blocks;
}

t_entry	*analyse_file(t_data *data, t_dir *dir, t_entry *entry, char *filename)
{
	if (dir)
		entry = entry_new(join_path(dir->path, filename), ft_strdup(filename));
	if (!entry || lstat(entry->path, &entry->stat) == -1)
	{
		if (dir)
			entry_free(entry);
		return (NULL);
	}
	_update_fields(data, dir, entry);
	if (dir)
		dir->total_files++;
	return (entry);
}
