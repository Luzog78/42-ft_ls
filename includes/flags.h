/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:33:26 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 11:33:19 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# define FLAGS_COUNT	14

# define FLAG_L			1
# define FLAG_RR		2
# define FLAG_A			4
# define FLAG_R			8
# define FLAG_T			16
# define FLAG_AA		32
# define FLAG_U			64
# define FLAG_F			128
# define FLAG_G			256
# define FLAG_D			512
# define FLAG_COLOR		1024
# define FLAG_CC		2048
# define FLAG_1			4096
# define FLAG_HELP		8192

# define C_FLAG_L		'l'
# define C_FLAG_RR		'R'
# define C_FLAG_A		'a'
# define C_FLAG_R		'r'
# define C_FLAG_T		't'
# define C_FLAG_AA		'A'
# define C_FLAG_U		'u'
# define C_FLAG_F		'f'
# define C_FLAG_G		'g'
# define C_FLAG_D		'd'
# define C_FLAG_COLOR	0
# define C_FLAG_CC		'C'
# define C_FLAG_1		'1'
# define C_FLAG_HELP	0

# define S_FLAG_L		"--long"
# define S_FLAG_RR		"--recursive"
# define S_FLAG_A		"--all"
# define S_FLAG_R		"--reverse"
# define S_FLAG_T		"--time"
# define S_FLAG_AA		"--almost-all"
# define S_FLAG_U		0
# define S_FLAG_F		0
# define S_FLAG_G		0
# define S_FLAG_D		"--directory"
# define S_FLAG_COLOR	"--color"
# define S_FLAG_CC		0
# define S_FLAG_1		0
# define S_FLAG_HELP	"--help"

# define DESC_L		"List in long format"
# define DESC_RR	"List subdirectories recursively"
# define DESC_A		"List all entries except for . and .."
# define DESC_R		"Reverse order while sorting"
# define DESC_T		"Sort by modification time, newest first"
# define DESC_AA	"List all entries including those starting with ."
# define DESC_U		"Use time of last access instead of last modification"
# define DESC_F		"Do not sort"
# define DESC_G		"List in long format without owner"
# define DESC_D		"List directory entries instead of contents"
# define DESC_COLOR	"Colorize the output"
# define DESC_CC	"List entries in columns"
# define DESC_1		"List one entry per line"
# define DESC_HELP	"Print this help"

int	get_c_flag(const char c);
int	get_s_flag(const char *s);

# ifndef __FLAGS_C__

extern const int	*g_flags;
extern const char	*g_c_flags;
extern const char	**g_s_flags;
extern const char	**g_desc_flags;

# endif

#endif
