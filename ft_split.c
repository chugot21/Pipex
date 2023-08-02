/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:26 by chugot            #+#    #+#             */
/*   Updated: 2023/04/20 11:40:27 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
			j++;
		i++;
	}
	return (j);
}

static int	*ft_lengthword(char const *s, char c)
{
	int	i;
	int	j;
	int	k;
	int	*length;

	i = 0;
	j = 0;
	length = (int *)malloc(sizeof(int) * (ft_countword(s, c)));
	if (length == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		k = 0;
		while (s[i] != '\0' && s[i] == c)
			i++;
		while (s[i] != '\0' && s[i] != c)
		{
			k++;
			i++;
		}
		if (k > 0)
			length[j++] = k;
	}
	return (length);
}

char	*ft_strcpy_split(char *tab, const char *s, int start, int end)
{
	int	i;

	i = 0;
	while (start != end && s[start] != '\0')
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split2(char **tab, int *lengthw, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			tab[j] = (char *)malloc(sizeof(char) * (lengthw[j] + 1));
			ft_strcpy_split(tab[j], s, i, i + lengthw[j]);
			i = i + lengthw[j];
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word;
	int		*lengthw;

	word = ft_countword(s, c);
	lengthw = ft_lengthword(s, c);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (tab == 0)
		return (NULL);
	ft_split2(tab, lengthw, s, c);
	free(lengthw);
	return (tab);
}
