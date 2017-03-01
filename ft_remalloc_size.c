/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 10:31:23 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/27 10:56:16 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	*ft_remalloc_size(size_t *data, size_t len_d, size_t len_s)
{
	int			x;
	size_t		*tmp_data;

	if (len_d <= len_s)
		return (data);
	x = 0;
	if (!(tmp_data = ft_memalloc((sizeof(size_t *) * len_d))))
		return (NULL);
	while (x < len_s)
	{
		tmp_data[x] = data[x];
		x++;
	}
	free(data);
	if (!(data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	ft_memset(data, 0, sizeof(char *) * len_d);
	x = 0;
	while (x < len_s)
	{
		data[x] = tmp_data[x];
		x++;
	}
	free(tmp_data);
	return (data);
}
