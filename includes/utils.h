/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:01:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/15 10:07:47 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "typedefs.h"

t_bool			ft_isalnum(char c);
char			*ft_itoa(int n);
void			*ft_malloc(size_t bytes);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *str);
unsigned char	ft_toupper(char c);
int				ft_strcmp(const char *s1, const char *s2);

void			write_error(t_data *data, char *msg);
void			write2(char *msg);

char			*get_time(time_t *_time);
char			*join_path(char *dir, char *name);
char			*remove_diacritics(char *str, t_bool alnum_only);
void			undiacritize(t_dir *dir);
int				undiacritics_sort(char *s1, char *s2);

t_strlst		*strlst_new(char *str);
void			strlst_add(t_strlst **lst, t_strlst *new);
void			strlst_free(t_strlst *lst);
size_t			strlst_len(t_strlst *lst);

t_entry			*entry_new(char *path, char *name);
void			entry_add(t_entry **lst, t_entry *new);
void			entry_free(t_entry *lst);
size_t			entry_len(t_entry *lst);

t_dir			*dir_new(char *path);
void			dir_add(t_dir **lst, t_dir *new);
void			dir_free(t_dir *lst);
size_t			dir_len(t_dir *lst);

#endif
