/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdong <jdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 12:41:09 by jdong         #+#    #+#                 */
/*   Updated: 2025/05/08 12:15:55 by jingyandong   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_elements(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	calulate_sep_s_len(char const *s, size_t start, char c)
{
	char	*end;
	size_t	str_len;

	end = ft_strchr(s + start, c);
	if (end)
		str_len = (size_t)(end - s) - start;
	else
		str_len = ft_strlen(s + start);
	return (str_len);
}

static char	*make_sep_s(char **arr, char const *s, size_t len, size_t arr_i)
{
	char	*sep_s;
	size_t	i;

	i = 0;
	sep_s = malloc(len + 1);
	if (!sep_s)
	{
		while (i < arr_i)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		return (NULL);
	}
	ft_strlcpy(sep_s, s, len + 1);
	return (sep_s);
}

static int	fill_sarr(char **sarr, char const *s, char c, size_t elements)
{
	size_t	i;
	size_t	start;
	size_t	str_len;

	i = 0;
	start = 0;
	while (i < elements && s[start])
	{
		while (s[start] == c)
			start++;
		str_len = calulate_sep_s_len(s, start, c);
		sarr[i] = make_sep_s(sarr, s + start, str_len, i);
		if (!sarr[i])
			return (0);
		start += str_len;
		i++;
	}
	sarr[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**sarr;
	size_t	nb_elements;

	if (!s)
		return (NULL);
	nb_elements = count_elements(s, c);
	sarr = malloc((nb_elements + 1) * sizeof(char *));
	if (!sarr)
		return (NULL);
	if (!fill_sarr(sarr, s, c, nb_elements))
		return (NULL);
	return (sarr);
}
