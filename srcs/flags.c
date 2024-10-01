/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:13:03 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 11:20:36 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __FLAGS_C__
#include "ft_ls.h"
#undef __FLAGS_C__

const int	*g_flags = (const int []){
	FLAG_L,
	FLAG_RR,
	FLAG_A,
	FLAG_R,
	FLAG_T,
	FLAG_AA,
	FLAG_U,
	FLAG_F,
	FLAG_G,
	FLAG_D,
	FLAG_COLOR,
	FLAG_CC,
	FLAG_1,
	FLAG_HELP
};

const char	*g_c_flags = (const char []){
	C_FLAG_L,
	C_FLAG_RR,
	C_FLAG_A,
	C_FLAG_R,
	C_FLAG_T,
	C_FLAG_AA,
	C_FLAG_U,
	C_FLAG_F,
	C_FLAG_G,
	C_FLAG_D,
	C_FLAG_COLOR,
	C_FLAG_CC,
	C_FLAG_1,
	C_FLAG_HELP
};

const char	**g_s_flags = (const char *[]){
	S_FLAG_L,
	S_FLAG_RR,
	S_FLAG_A,
	S_FLAG_R,
	S_FLAG_T,
	S_FLAG_AA,
	S_FLAG_U,
	S_FLAG_F,
	S_FLAG_G,
	S_FLAG_D,
	S_FLAG_COLOR,
	S_FLAG_CC,
	S_FLAG_1,
	S_FLAG_HELP
};

const char	**g_desc_flags = (const char *[]){
	DESC_L,
	DESC_RR,
	DESC_A,
	DESC_R,
	DESC_T,
	DESC_AA,
	DESC_U,
	DESC_F,
	DESC_G,
	DESC_D,
	DESC_COLOR,
	DESC_CC,
	DESC_1,
	DESC_HELP
};

int	get_c_flag(const char c)
{
	int	i;

	if (!c)
		return (0);
	i = 0;
	while (i < FLAGS_COUNT)
	{
		if (g_c_flags[i] == c)
			return (g_flags[i]);
		i++;
	}
	return (0);
}

int	get_s_flag(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (i < FLAGS_COUNT)
	{
		if (ft_strcmp(g_s_flags[i], s) == 0)
			return (g_flags[i]);
		i++;
	}
	return (0);
}
