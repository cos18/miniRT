/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:12:06 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:22:04 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int				main(int argv, char **argc)
{
	t_rt		*rt;
	void		*mlx;
	t_list		*camlst;
	t_img_data	*img;

	if (argv < 2 || argv > 3 ||
			(argv == 3 && (ft_strncmp(argc[2], "--save", 6) != 0)))
		return (ft_printf("Wrong argc\n"));
	rt = parse_file(argc[1], 3 - argv);
	camlst = rt->camlst;
	while (camlst && camlst->content)
	{
		draw_hittable_pthread(camlst->content, rt);
		camlst = camlst->next;
	}
	img = ((t_camera *)(rt->camlst->content))->data;
	mlx = rt->mlx;
	if (mlx)
		mlx_show(img, "miniRT", mlx);
	else
		save_bmp(img, argc[1]);
	free_rt(rt);
	while (1)
		(void)rt;
}
