/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:08:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/13 17:14:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*dir_new(char *path)
{
	t_dir	*new;

	if (!path)
		return (NULL);
	new = (t_dir *) ft_malloc(sizeof(t_dir));
	if (!new)
		return (NULL);
	new->path = path;
	return (new);
}

void	dir_add(t_dir **lst, t_dir *new)
{
	t_dir	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	dir_free(t_dir *lst)
{
	t_dir	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->undiacritized);
		free(lst->name);
		free(lst->path);
		entry_free(lst->entries);
		free(lst);
		lst = tmp;
	}
}

size_t	dir_len(t_dir *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
