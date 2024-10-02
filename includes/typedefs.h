/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:34:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/02 11:42:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef struct stat			t_stat;
typedef unsigned long long	t_ull;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_sort
{
	DEFAULT_SORT,
	DIR_SORT,
	LAST_MODIF_SORT,
	LAST_ACCESS_SORT,
}	t_sort;

typedef struct s_strlst
{
	char			*str;
	struct s_strlst	*next;
}					t_strlst;

typedef struct s_entry
{
	char			*path;
	char			*name;

	t_stat			stat;

	char			type;
	char			rights[9];
	size_t			nlink;
	char			*owner;
	char			*group;
	size_t			major;
	size_t			size;
	char			*date;

	char			*linked_to;
	char			*color;

	struct s_entry	*next;
}					t_entry;

typedef struct s_dir
{
	char			*path;
	char			*name;
	t_entry			*entries;

	t_ull			total_blocks;

	size_t			nlink_len;
	size_t			owner_len;
	size_t			group_len;
	size_t			major_len;
	size_t			size_len;
	size_t			date_len;
	size_t			name_len;
	char			*chmod_format;
	char			*owner_format;
	char			*group_format;
	char			*major_format;
	char			*size_format;
	char			*date_format;
	char			*name_format;

	struct s_dir	*next;
}					t_dir;

typedef struct s_data
{
	char		*argv0;
	int			flags;
	t_sort		sort;
	t_bool		dir_title;
	t_strlst	*path;
	t_dir		*dirs;
}				t_data;

#endif
