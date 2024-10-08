/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undiacritics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:59:45 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/07 10:59:35 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	undiacritize(t_dir *dir)
{
	t_entry	*tmp;

	tmp = dir->entries;
	while (tmp)
	{
		tmp->undiacritized = remove_diacritics(tmp->path, FALSE);
		if (!tmp->undiacritized)
			tmp->undiacritized = ft_strdup(tmp->path);
		tmp = tmp->next;
	}
}

static void	_increment_ij(char *s1, char *s2, size_t *i, size_t *j)
{
	(*i)++;
	while (s1[*i] && !ft_isalnum(s1[*i]))
		(*i)++;
	(*j)++;
	while (s2[*j] && !ft_isalnum(s2[*j]))
		(*j)++;
}

int	undiacritics_sort(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j] && ft_toupper(s1[i]) == ft_toupper(s2[j]))
		_increment_ij(s1, s2, &i, &j);
	if (s1[i] != s2[j])
		return (ft_toupper(s1[i]) - ft_toupper(s2[j]));
	i = 0;
	j = 0;
	while (s1[i] && s2[j] && s1[i] == s2[j])
		_increment_ij(s1, s2, &i, &j);
	if (s1[i] != s2[j])
		return (s2[j] - s1[i]);
	return (ft_strcmp(s1, s2));
}
