/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:39:41 by gsotty            #+#    #+#             */
/*   Updated: 2016/11/11 16:10:29 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		x;
	size_t	y;

	x = 0;
	y = 0;
	if (s2[x] == '\0')
		return ((char *)s1);
	while (s1[x] != '\0')
	{
		y = 0;
		while (s2[y] == s1[x + y])
		{
			if (s2[y + 1] == '\0')
				return ((char *)s1 + x);
			y++;
		}
		x++;
	}
	return (NULL);
}
