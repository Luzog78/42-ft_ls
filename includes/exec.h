/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:39:47 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/07 09:26:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ft_ls.h"

# define MAX_COLUMNS	100

/* ************************************************************************** */
/*                            Phase 1: Extraction                             */
/* ************************************************************************** */

int		analyse_dir(t_data *data, t_dir *dir);
char	analysis_get_type(mode_t mode);
void	analysis_get_rights(char *rights, mode_t mode);
char	*analysis_get_owner(uid_t uid);
char	*analysis_get_group(gid_t gid);
char	*analysis_get_linked_to(char *path);

/* ************************************************************************** */
/*                           Phase 2: Normalization                           */
/* ************************************************************************** */

int		normalise_entries(t_data *data, t_dir *dir);
void	set_dir_formats(t_data *data, t_dir *dir);

/* ************************************************************************** */
/*                              Phase 3: Sorting                              */
/* ************************************************************************** */

void	sort_entries(t_data *data, t_dir *dir);

/* ************************************************************************** */
/*                             Phase 4: Printing                              */
/* ************************************************************************** */

int		print_entries(t_data *data, t_dir *dir, t_bool has_next);
int		print_entries_lines(t_data *data, t_dir *dir);

#endif
