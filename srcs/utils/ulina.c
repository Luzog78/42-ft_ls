/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulina.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:14:31 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 11:42:54 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief ul (unsigned long) in a (alpha). Write the number IN the string.
 * 
 * @param str The length-th position of the string. (It will go backward)
 * 
 * @note Example: unila("0000" + 4, 1234) => "1234"
 */
void	ulina(char *str, unsigned long n)
{
	while (n)
	{
		*--str = n % 10 + '0';
		n /= 10;
	}
}
