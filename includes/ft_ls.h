/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:03:20 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 12:54:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ft_printf.h"
# include "flags.h"
# include "typedefs.h"
# include "utils.h"

int	parse(t_data *data, int argc, char **argv);
int	exec(t_data *data);

#endif
