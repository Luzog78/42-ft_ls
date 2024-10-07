/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:25:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/07 09:25:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	analysis_get_type(mode_t mode)
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

void	analysis_get_rights(char *rights, mode_t mode)
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

char	*analysis_get_owner(uid_t uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(uid);
	if (!pwd)
		return (ft_itoa(uid));
	return (ft_strdup(pwd->pw_name));
}

char	*analysis_get_group(gid_t gid)
{
	struct group	*grp;

	grp = getgrgid(gid);
	if (!grp)
		return (ft_itoa(gid));
	return (ft_strdup(grp->gr_name));
}

char	*analysis_get_linked_to(char *path)
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
