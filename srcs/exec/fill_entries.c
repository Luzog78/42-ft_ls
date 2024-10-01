/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:13:49 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/01 16:17:18 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * Let's admit, for the example, that we have this filetree :
 * 
 * .
 * ├── a
 * │   ├── file1
 * │   └── file2
 * ├── b
 * │   ├── file3
 * │   └── file4
 * └── c
 *     ├── file5
 *     └── dir
 *         └── file6
 */
int	fill_entries(t_data *data)
{
	t_dir	*o = dir_new(ft_strdup("."));
	t_entry	*d_a = entry_new(ft_strdup("a"));
	t_entry	*d_b = entry_new(ft_strdup("b"));
	t_entry	*d_c = entry_new(ft_strdup("c"));

	t_dir	*a = dir_new(ft_strdup("a"));
	t_entry	*file1 = entry_new(ft_strdup("a/file1"));
	t_entry	*file2 = entry_new(ft_strdup("a/file2"));

	t_dir	*b = dir_new(ft_strdup("b"));
	t_entry	*file3 = entry_new(ft_strdup("b/file3"));
	t_entry	*file4 = entry_new(ft_strdup("b/file4"));

	t_dir	*c = dir_new(ft_strdup("c"));
	t_entry	*file5 = entry_new(ft_strdup("c/file5"));
	t_entry	*d_dir = entry_new(ft_strdup("c/dir"));

	t_dir	*dir = dir_new(ft_strdup("c/dir"));
	t_entry	*file6 = entry_new(ft_strdup("c/dir/file6"));

	entry_add(&o->entries, d_a);
	entry_add(&o->entries, d_b);
	entry_add(&o->entries, d_c);

	entry_add(&a->entries, file1);
	entry_add(&a->entries, file2);

	entry_add(&b->entries, file3);
	entry_add(&b->entries, file4);

	entry_add(&c->entries, file5);
	entry_add(&c->entries, d_dir);

	entry_add(&dir->entries, file6);
	
	dir_add(&o, a);
	dir_add(&o, b);
	dir_add(&o, c);
	dir_add(&o, dir);
	data->dirs = o;
	return (0);
}
