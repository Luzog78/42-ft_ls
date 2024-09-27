/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:08:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/09/27 12:27:08 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*dir_new(char *path)
{
	t_dir	*new;

	if (!path)
		return (NULL);
	new = (t_dir *) malloc(sizeof(t_dir));
	if (!new)
		return (NULL);
	new->path = path;
	new->entries = NULL;
	new->next = NULL;
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
		free(lst->path);
		entry_free(lst->entries);
		free(lst);
		lst = tmp;
	}
}
