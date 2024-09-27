/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:01:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/09/27 15:20:43 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "typedefs.h"

char		*ft_strdup(const char *s1);

t_strlst	*strlst_new(char *str);
void		strlst_add(t_strlst **lst, t_strlst *new);
void		strlst_free(t_strlst *lst);

t_entry		*entry_new(char *path);
void		entry_add(t_entry **lst, t_entry *new);
void		entry_free(t_entry *lst);

t_dir		*dir_new(char *path);
void		dir_add(t_dir **lst, t_dir *new);
void		dir_free(t_dir *lst);

#endif
