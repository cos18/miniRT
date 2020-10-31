/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:12:06 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/31 17:53:26 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int				main(int argv, char **argc)
{
	t_rt		*rt;
	void		*mlx;
	t_list		*camlst;

	if (argv < 2 || argv > 3 ||
			(argv == 3 && (ft_strncmp(argc[2], "--save", 6) != 0)))
		return (ft_printf("Wrong argc\n"));
	rt = parse_file(argc[1], 3 - argv);
	camlst = rt->camlst;
	while (camlst && camlst->content)
	{
		draw_hittable_pthread(camlst->content, rt->hitlst);
		camlst = camlst->next;
	}
	camlst = rt->camlst;
	mlx = rt->mlx;
	free_rt(rt);
	if (mlx)
		mlx_show(((t_camera *)camlst)->data, "miniRT", mlx);
	else
		save_bmp(((t_camera *)camlst)->data, argc[1]);
	free_camlst(camlst);
	while (1)
		(void)rt;
}
