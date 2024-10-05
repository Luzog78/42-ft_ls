/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:08:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/05 15:43:08 by ysabik           ###   ########.fr       */
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
		free(lst->chmod_format);
		free(lst->owner_format);
		free(lst->group_format);
		free(lst->major_format);
		free(lst->major_spacing);
		free(lst->size_format);
		free(lst->date_format);
		free(lst->name_format);
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
