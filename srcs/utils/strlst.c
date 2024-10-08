/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:59:08 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 19:57:35 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_strlst	*strlst_new(char *str)
{
	t_strlst	*new;

	if (!str)
		return (NULL);
	new = (t_strlst *) ft_malloc(sizeof(t_strlst));
	if (!new)
		return (NULL);
	new->str = str;
	return (new);
}

void	strlst_add(t_strlst **lst, t_strlst *new)
{
	t_strlst	*tmp;

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

void	strlst_free(t_strlst *lst)
{
	t_strlst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->str);
		free(lst);
		lst = tmp;
	}
}

size_t	strlst_len(t_strlst *lst)
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
