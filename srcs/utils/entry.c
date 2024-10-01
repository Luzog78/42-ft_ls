/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:03:28 by ysabik            #+#    #+#             */
/*   Updated: 2024/09/27 15:29:10 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	reset_rights(t_entry *entry)
{
	int	i;

	i = 0;
	while (i < 9)
		entry->rights[i++] = '-';
}

t_entry	*entry_new(char *path)
{
	t_entry	*new;

	if (!path)
		return (NULL);
	new = (t_entry *) malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->path = path;
	new->name = NULL;
	new->type = 0;
	reset_rights(new);
	new->hidden = FALSE;
	new->nlink = 0;
	new->owner = NULL;
	new->group = NULL;
	new->size = 0;
	new->mtime = 0;
	new->linked_to = NULL;
	new->color = NULL;
	new->next = NULL;
	return (new);
}

void	entry_add(t_entry **lst, t_entry *new)
{
	t_entry	*tmp;

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

void	entry_free(t_entry *lst)
{
	t_entry	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->path);
		free(lst->name);
		free(lst->owner);
		free(lst->group);
		free(lst->linked_to);
		free(lst->color);
		free(lst);
		lst = tmp;
	}
}

size_t	entry_len(t_entry *lst)
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
