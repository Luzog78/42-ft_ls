/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:39:47 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 17:05:31 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ft_ls.h"

int	fill_entries(t_data *data);

int	analyse_entries(t_data *data, t_dir *dir, t_dir **new_list);

int	print_entries(t_data *data, t_dir *dir, t_bool has_next);

#endif
