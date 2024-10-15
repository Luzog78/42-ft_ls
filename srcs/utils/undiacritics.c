/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undiacritics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:59:45 by ysabik            #+#    #+#             */
/*   Updated: 2024/10/14 20:05:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	undiacritize(t_dir *dir)
{
	t_entry	*tmp;

	tmp = dir->entries;
	while (tmp)
	{
		tmp->undiacritized = remove_diacritics(tmp->name, FALSE);
		if (!tmp->undiacritized)
			tmp->undiacritized = ft_strdup(tmp->name);
		tmp->undiacritized_len = ft_strlen(tmp->undiacritized);
		tmp = tmp->next;
	}
}

static void	_increment_ij(char *s1, char *s2, size_t *i, size_t *j)
{
	(*i)++;
	while (s1[*i] && !ft_isalnum(s1[*i]))
		(*i)++;
	(*j)++;
	while (s2[*j] && !ft_isalnum(s2[*j]))
		(*j)++;
}

/**
 * An "exception" is when the chars of the current string at the current index
 *   follow this syntax: `<alnum><special><alnum>`, only if the `<special>`
 *   char is at least at the 3rd index (i >= 2).
 * 
 * `met1` and `met2` are FALSE by default.
 * They describes if, respectively, `s1` and `s2`
 *   have met 2 same special chars consecutively.
 * If it's the case, the next `<alnum><special><alnum>`
 *   will not be considered as "exceptions".
 * 
 * -> Exceptions: `ab-c` `ab+c` `ab_c`
 * -> Not exceptions: `-abc` `a-bc` `ab--c` `ab++c` `ab__c`
 * 
 * ---
 * 
 * Rules of sorting :
 * 
 * If ex1 and ex2  ==>  If `s1` and `s2` are "in exception" at `i`
 * | Then sort by ascii `s1[i]` and `s2[i]`.
 * Exemple:
 * -> `ab-c` ; `ab+c` >> `-` < `+` so `ab-c` < `ab+c`
 * 
 * If (only) ex1
 * | Then s1 HAS to get first (return -1).
 * Exemple:
 * -> `ab-c` < `ab--c`
 * -> `ab+c` < `ab+++c`
 * 
 * If (only) ex2
 * | Then s2 HAS to get first (return 1).
 */
static int	_exception(char *s1, char *s2, t_bool met1, t_bool met2)
{
	size_t	i;
	t_bool	ex1;
	t_bool	ex2;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (i >= 2 && !ft_isalnum(s1[i]) && !ft_isalnum(s2[i]))
		{
			ex1 = ft_isalnum(s1[i + 1]) && ft_isalnum(s1[i - 1]) && !met1;
			ex2 = ft_isalnum(s2[i + 1]) && ft_isalnum(s2[i - 1]) && !met2;
			if (ex1 && ex2)
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
			if (ex2)
				return (1);
			if (ex1)
				return (-1);
		}
		if (!ft_isalnum(s1[i]) && s1[i] == s1[i + 1])
			met1 = TRUE;
		if (!ft_isalnum(s2[i]) && s2[i] == s2[i + 1])
			met2 = TRUE;
		i++;
	}
	return (0);
}

/**
 * Though one !
 *
 * 1. Sort only the alnum chars case-insensitivitely (by upper ascii)
 *     -> `aaa` < `bbb`
 *     -> `ABC` = `abc`
 *     -> `123` < `abc`
 *
 * 2. Sort the alnum char case-sensivitely (by reversed ascii)
 *     -> `aaa` < `aaA` < `aAa` < `aAA` < `Aaa` < ...
 *     -> `ABC` > `abc`
 *     -> `123` = `123`
 *
 * 3. There is an very wierd exception when 
 *    `<alnums (at least 2)><same specials><text>`
 *    like `ab-c`, `ab--c`, `ab---c`, `ab+c`, `ab++c` and `ab+++c`.
 *    The order will be :
 *      * `ab-c`
 *      * `ab+c`
 *      * `ab---c`
 *      * `ab--c`
 *      * `ab+++c`
 *      * `ab++c`
 * 
 * 4. If there is no exception, sort by ascii (ft_strcmp).
 *
 * ---
 *
 * Exemple of test folder:
 * - 123
 * - 421 abc
 * - 421-abc
 * - 421   abc
 * - 421  abc
 * - 421---abc
 * - 421--abc
 * - 42ft
 * - 42 ft_print
 * - 42 ft_printf
 * - 42&ft_printf
 * - 42-ft_printf
 * - 42ft_printf
 * - 42                       ft_printf
 * - 42      ft_printf
 * - 42     ft_printf
 * - 42    ft_printf
 * - 42   ft_printf
 * - 42  ft  printf
 * - 42  ft printf
 * - 42  ft--printf
 * - 42  ft-printf
 * - 42  ft__printf
 * - 42  ft_printf
 * - 42 ft_printg
 * - 42 gt_print
 * - a
 * - %%a
 * - &a
 * - + a
 * - +|a
 * - \-a
 * - ~a
 * - a0000 bc
 * - a0000-bc
 * - a0000]bc
 * - a0000   bc
 * - a0000  bc
 * - a0000---bc
 * - a0000--bc
 * - a0000]]]bc
 * - a0000]]bc
 * - a00 bc
 * - a00-bc
 * - a00   bc
 * - a00  bc
 * - a00 -bc
 * - a00---bc
 * - a00--bc
 * - aaa
 * - aaA
 * - aAA
 * - Aaa
 * - AAa
 * - AAA
 * - abc
 * - abc
 * - abc
 * - @@@abc
 * - @@abc
 * - @abc
 * - a   bc
 * - a  bc
 * - a -bc
 * - a bc
 * - a---bc
 * - a--bc
 * - a-bc
 * - abcc
 * - abc.tar
 * - build
 * - éa
 * - en.subject.pdf
 * - éx
 * - ft_ls
 * - includes
 * - Makefile
 * - srcs
 * - test
 * - TTT
 * - &x
 * - \-x
 * - ~x
 * - xxx
 */
int	undiacritics_sort(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	int		exception_result;

	i = -1;
	j = -1;
	_increment_ij(s1, s2, &i, &j);
	while (s1[i] && s2[j] && ft_toupper(s1[i]) == ft_toupper(s2[j]))
		_increment_ij(s1, s2, &i, &j);
	if (s1[i] != s2[j])
		return (ft_toupper(s1[i]) - ft_toupper(s2[j]));
	i = -1;
	j = -1;
	_increment_ij(s1, s2, &i, &j);
	while (s1[i] && s2[j] && s1[i] == s2[j])
		_increment_ij(s1, s2, &i, &j);
	if (s1[i] != s2[j])
		return (s2[j] - s1[i]);
	exception_result = _exception(s1, s2, FALSE, FALSE);
	if (exception_result)
		return (exception_result);
	return (ft_strcmp(s1, s2));
}
