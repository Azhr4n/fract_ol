/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:35:14 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 16:35:15 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

static int	get_number_of_words(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s)
	{
		if (count == 0 || (*s == c && *(s + 1) != c && *(s + 1)))
			count++;
		s++;
	}
	return (count);
}

static int	get_len_of_word(char const *s, char c)
{
	int		len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static void	fill_tab(char ***ret, int len, char const *s, char c)
{
	int		i;
	int		j;
	int		len_word;
	char	**ptr;

	ptr = *ret;
	i = -1;
	while (++i < len)
	{
		len_word = get_len_of_word(s, c);
		ptr[i] = (char *)malloc(sizeof(char) * (len_word + 1));
		if (ptr[i] != NULL)
		{
			ptr[i][len_word] = 0;
			j = 0;
			while (j < len_word)
			{
				ptr[i][j] = s[j];
				j++;
			}
			s = s + j;
			while (*s == c)
				s++;
		}
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		nb_words;

	while (*s == c)
		s++;
	nb_words = get_number_of_words(s, c);
	if ((ret = (char **)malloc(sizeof(char *) * (nb_words + 1))) == NULL)
		return (NULL);
	ret[nb_words] = 0;
	fill_tab(&ret, nb_words, s, c);
	return (ret);
}
