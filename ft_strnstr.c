/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:49:21 by chugot            #+#    #+#             */
/*   Updated: 2023/04/17 13:49:26 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (big == 0 && len == 0)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	if (little[i] == 0)
		return ((char *) big);
	while (big[i] != 0 && k < len)
	{
		while (big[i] && little[j] && big[i] == little[j] && (k + j) < len)
		{
			i++;
			j++;
			if (little[j] == 0)
				return ((char *)big + i - j);
		}
		k++;
		i = k;
		j = 0;
	}
	return (NULL);
}
