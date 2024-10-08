/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalise_entries.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:44:23 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/07 11:32:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	_ends_with(const char *str, const char *end)
{
	int		i;
	int		j;

	if (!str || !end)
		return (!str && !end);
	i = 0;
	while (str[i])
		i++;
	j = 0;
	while (end[j])
		j++;
	if (i < j)
		return (FALSE);
	while (j >= 0)
	{
		if (ft_toupper(str[i]) != ft_toupper(end[j]))
			return (FALSE);
		i--;
		j--;
	}
	return (TRUE);
}

static t_bool	_match(const char **arr, const char *path)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (_ends_with(path, arr[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * Archive extensions tested : .a .ar .cpio .shar .LBR .iso .lbr .mar .sbx .tar
 * .br .bz2 .F '.?XF' .genozip .gz .lz .lz4 .lzma .lzo .rz .sfark .sz '.?Q?'
 * '.?Z?' .xz .z .Z .zst '.??_' .7z .s7z .aar .ace .afa .alz .apk .arc .ark .cdx
 * .arj .b1 .b6z .ba .bh .cab .car .cfs .cpt .dar .dd .dgc .dmg .ear .gca .ha
 * .hki .ice .jar .kgb .lzh .lha .lzx .pak .prtimg .paq6 .paq7 .paq8 .pea .phar
 * .pim .pit .qda .rar .rk .sda .sen .sfx .shk .sit .sitx .sqx .tar.gz .tgz
 * .tar.Z .tar.bz2 .tbz2 .tar.lz .tlz .tar.xz .txz .tar.zst .uc .uc0 .uc2 .ucn
 * .ur2 .ue2 .uca .uha .war .wim .xar .xp3 .yz1 .zip .zipx .zoo .zpaq .zz .ecc
 * .ecsbx .par .par2 .rev
 * 
 * Audio/Graphic file extensions tested : .3gp .aif .aiff .au .avi .bmp .cur
 * .flac .gif .jpeg .l16 .m4r .mogg .mp3 .mpeg-2 .odt .ogg .png .swf .tiff .wave
 * .webp .wmv .aac .aifc .alac .avchd .avif .caf .f4v .flv .ico .jpg .m4a .mkv
 * .mov .mp4 .mpeg2 .oga .pcm .svg .tif .wav .webm .wma
 */
static t_bool	_is_file(const char *path, int file_type)
{
	const char	**archive = (const char *[38]) {
		".7z", ".ace", ".alz", ".arc", ".arj", ".bz2", ".cab", ".cpio", ".ear",
		".gz", ".jar", ".lha", ".lz", ".lz4", ".lzh", ".lzma", ".lzo", ".rar",
		".rz", ".tar", ".tar.bz2", ".tar.gz", ".tar.lz", ".tar.xz", ".tar.Z",
		".tbz2", ".tgz", ".tlz", ".txz", ".war", ".wim", ".xz", ".z", ".zip",
		".zoo", ".zst", NULL
	};
	const char	**audio_graphic = (const char *[18]) {
		".avi", ".avif", ".bmp", ".flv", ".gif", ".jpeg", ".jpg", ".mkv",
		".mov", ".mp4", ".png", ".svg", ".tif", ".tiff", ".webm", ".webp",
		".wmv", NULL
	};
	const char	**audio = (const char *[10]) {
		".aac", ".au", ".flac", ".m4a", ".mp3", ".oga", ".ogg", ".wav", NULL
	};

	if (file_type == 0)
		return (_match(archive, path));
	else if (file_type == 1)
		return (_match(audio_graphic, path));
	else if (file_type == 2)
		return (_match(audio, path));
	return (FALSE);
}

static void	apply_color(t_dir *dir)
{
	t_entry	*entry;
	
	entry = dir->entries;
	while (entry)
	{
		if (entry->type == 'd')
			entry->color = ft_strjoin(COLR_BOLD, COLR_BLUE);
		else if (entry->type == 'l')
			entry->color = ft_strjoin(COLR_BOLD, COLR_CYAN);
		else if (entry->rights[2] == 'x' || entry->rights[5] == 'x'
			|| entry->rights[8] == 'x')
			entry->color = ft_strjoin(COLR_BOLD, COLR_GREEN);
		else if (entry->type == 'p' || entry->type == 'b' || entry->type == 'c')
			entry->color = ft_strjoin(COLR_BOLD, COLR_YELLOW);
		else if (entry->type == 's' || _is_file(entry->path, 1))
			entry->color = ft_strjoin(COLR_BOLD, COLR_MAGENTA);
		else if (_is_file(entry->path, 0))
			entry->color = ft_strjoin(COLR_BOLD, COLR_RED);
		else if (_is_file(entry->path, 2))
			entry->color = ft_strdup(COLR_CYAN);
		entry = entry->next;
	}
}

int	normalise_entries(t_data *data, t_dir *dir)
{
	set_dir_formats(data, dir);
	if (data->flags & FLAG_COLOR)
		apply_color(dir);
	return (0);
}
