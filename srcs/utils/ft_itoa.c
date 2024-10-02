/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:49:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 13:50:04 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	nbrlen(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = nbrlen(n);
	str = (char *) ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	if (len == 1)
		str[0] = '0';
	return (str);
}
