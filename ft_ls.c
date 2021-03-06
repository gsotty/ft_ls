/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:06:35 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/23 11:02:38 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(int argc, char **argv, int test, t_struc_ls *struc)
{
	int		cont_arg_1;

	cont_arg_1 = 0;
	if ((struc->buf.stat = ft_memalloc(sizeof(STAT *) * argc)) == NULL)
		return ;
	if ((struc->buf.buf = ft_memalloc(sizeof(char **) * argc)) == NULL)
		return ;
	if ((struc->buf.xattr = ft_memalloc(sizeof(size_t *) * argc)) == NULL)
		return ;
	if ((struc->buf.cont_files = ft_memalloc(sizeof(int) * argc)) == NULL)
		return ;
	if ((struc->buf.save_name = ft_memalloc(sizeof(char *) * argc)) == NULL)
		return ;
	if ((struc->buf.files_or_dir = ft_memalloc(sizeof(size_t) * argc)) == NULL)
		return ;
	while (cont_arg_1 < argc)
	{
		ft_while_ls(argv[cont_arg_1], test, struc);
		cont_arg_1++;
	}
	write_buf_ls(struc->buf.save_name, test, struc, struc->len.total);
}

int		main(int argc, char **argv)
{
	int			cont_arg;
	t_struc_ls	struc;

	ft_memset(&struc, 0, sizeof(t_struc_ls));
	cont_arg = check_flag_ls(argc, argv, &struc);
	ft_ls(struc.buf.argc - cont_arg, argv + cont_arg, 1, &struc);
	return (1);
}
