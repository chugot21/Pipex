/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:13:07 by chugot            #+#    #+#             */
/*   Updated: 2023/04/19 14:13:09 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	length;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	length = ft_strlen((char *) s1) + ft_strlen((char *) s2);
	new = (char *) malloc(sizeof(char) * (length + 2));
	if (new == 0)
		return (NULL);
	while (i <= length)
	{	
		while (i < ft_strlen((char *) s1))
		{
			new[i] = s1[i];
			i++;
		}
		new[i] = s2[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
