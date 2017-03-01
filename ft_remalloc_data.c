/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 10:46:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/27 10:56:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**ft_remalloc_data(char **data, size_t len_d, size_t len_s)
{
	int			x;
	char		**tmp_data;

	if (len_d <= len_s)
		return (data);
	x = 0;
	if (!(tmp_data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	while (x < len_s)
	{
		tmp_data[x] = ft_strdup(data[x]);
		free(data[x]);
		x++;
	}
	if (!(data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	ft_memset(data, 0, sizeof(char *) * len_d);
	x = 0;
	while (x < len_s)
	{
		data[x] = ft_strdup(tmp_data[x]);
		free(tmp_data[x]);
		x++;
	}
	return (data);
}
