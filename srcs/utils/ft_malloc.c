/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:57:51 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 20:00:20 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_malloc(size_t bytes)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char *) malloc(bytes);
	i = 0;
	while (i < bytes)
		mem[i++] = 0;
	return ((void *) mem);
}
