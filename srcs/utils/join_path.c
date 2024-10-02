/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:23:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 15:41:47 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*join_path(char *dir, char *name)
{
	char	*path;
	size_t	i;

	path = (char *) ft_malloc(ft_strlen(dir) + ft_strlen(name) + 2);
	if (!path)
		return (NULL);
	i = 0;
	while (*dir)
		path[i++] = *dir++;
	if (path[i - 1] != '/')
		path[i++] = '/';
	while (*name)
		path[i++] = *name++;
	path[i] = '\0';
	return (path);
}
