/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:49:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/06 14:54:56 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	get_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISREG(mode))
		return ('-');
	return ('?');
}

static void	get_rights(char *rights, mode_t mode)
{
	short	i;

	rights[0] = !!(mode & S_IRUSR) * 'r';
	rights[1] = !!(mode & S_IWUSR) * 'w';
	rights[2] = !!(mode & S_IXUSR) * 'x';
	rights[3] = !!(mode & S_IRGRP) * 'r';
	rights[4] = !!(mode & S_IWGRP) * 'w';
	rights[5] = !!(mode & S_IXGRP) * 'x';
	rights[6] = !!(mode & S_IROTH) * 'r';
	rights[7] = !!(mode & S_IWOTH) * 'w';
	rights[8] = !!(mode & S_IXOTH) * 'x';
	rights[9] = '\0';
	i = 0;
	while (i < 9)
	{
		if (!rights[i])
			rights[i] = '-';
		i++;
	}
}

static char	*get_owner(uid_t uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(uid);
	if (!pwd)
		return (ft_itoa(uid));
	return (ft_strdup(pwd->pw_name));
}

static char	*get_group(gid_t gid)
{
	struct group	*grp;

	grp = getgrgid(gid);
	if (!grp)
		return (ft_itoa(gid));
	return (ft_strdup(grp->gr_name));
}

static char	*get_linked_to(char *path)
{
	char	*linked_to;
	ssize_t	len;

	linked_to = (char *) ft_malloc(1024);
	if (!linked_to)
		return (NULL);
	len = readlink(path, linked_to, 1023);
	if (len == -1)
	{
		free(linked_to);
		return (NULL);
	}
	linked_to[len] = '\0';
	return (linked_to);
}

static t_entry	*analyse_dirent(t_data *data, t_dir *dir, struct dirent *file)
{
	t_entry	*entry;

	entry = entry_new(dir->path, ft_strdup(file->d_name));
	if (!entry || lstat(entry->path, &entry->stat) == -1)
		return (entry_free(entry), NULL);
	entry->type = get_type(entry->stat.st_mode);
	get_rights(entry->rights, entry->stat.st_mode);
	entry->nlink = entry->stat.st_nlink;
	entry->owner = get_owner(entry->stat.st_uid);
	entry->group = get_group(entry->stat.st_gid);
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
		entry->linked_to = get_linked_to(entry->path);
	dir->total_files++;
	return (entry);
}

int	analyse_dir(t_data *data, t_dir *dir)
{
	struct dirent	*file;

	dir->name = ft_strdup(dir->path); // TODO: here to get the userfriendly name
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
		if (file->d_name[0] == '.' && !(data->flags & (FLAG_AA | FLAG_A)))
			continue ;
		entry_add(&dir->entries, analyse_dirent(data, dir, file));
	}
	closedir(dir->dir);
	return (0);
}
