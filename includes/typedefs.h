/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:34:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/11 11:26:38 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include <sys/sysmacros.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

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
	size_t			name_len;
	char			*undiacritized;
	size_t			undiacritized_len;

	t_stat			stat;

	char			type;
	char			rights[10];
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
	char			*undiacritized;
	t_entry			*entries;

	DIR				*dir;

	t_ull			total_files;
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
	char			*major_spacing;
	char			*size_format;
	char			*date_format;
	char			*name_format;

	struct s_dir	*next;
}					t_dir;

typedef struct s_data
{
	char			*argv0;
	int				flags;
	t_sort			sort;
	t_bool			dir_title;
	t_dir			*dirs;

	unsigned short	ws_row;
	unsigned short	ws_col;
	t_bool			is_tty;
}				t_data;

#endif
