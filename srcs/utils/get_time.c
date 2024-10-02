/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:37:20 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 14:49:04 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
}

char	*get_time(time_t *_time)
{
	char	*str;
	char	*ct;

	str = (char *) ft_malloc(sizeof(char) * 13);
	if (!str)
		return (NULL);
	ct = ctime(_time);
	if (!ct)
	{
		free(str);
		return (NULL);
	}
	if (time(NULL) - *_time > 15778463)
	{
		ft_memcpy(str, ct + 4, 7);
		ft_memcpy(str + 7, ct + 19, 5);
	}
	else
		ft_memcpy(str, ct + 4, 12);
	return (str);
}
