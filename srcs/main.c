/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:12:06 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/30 21:23:17 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				main(int argv, char **argc)
{
	t_rt		*rt;
	t_hittable	*obj;

	if (argv < 2 || argv > 3 ||
			(argv == 3 && (ft_strncmp(argc[2], "--save", 6) != 0)))
		return (ft_printf("Wrong argc\n"));
	rt = parse_file(argc[1]);
	obj = rt->hitlst->content;
	vec_print(obj->mat->color);
	vec_print(rt->amb_light);
	printf("%d %d\n", rt->img->width, rt->img->height);
	vec_print(((t_camera *)(rt->camlst->content))->origin);
	free_rt(rt);
}
