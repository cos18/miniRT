/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hittable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 04:55:05 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 22:21:16 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void				get_hittable_color(t_list *hitlst,
											t_hitlst_info *info,
											t_list *lightlst,
											t_vec *color)
{
	t_light_hit_info	*linfo;
	t_vec				*target;
	t_vec				*light;

	if (hitlst_hit(hitlst, info))
	{
		target = vec_mul_each(info->rec->mat->color, info->rec->mat->amb);
		linfo = lhit_info_new(info->rec->p, info->rec->normal, info->ray);
		light = lightlst_hit(lightlst, hitlst, linfo);
		vec_mul_each_apply(light, info->rec->mat->color);
		vec_add_apply(target, light);
		free(light);
		free_lhit_info(linfo);
	}
	else
		target = vec_new(0, 0, 0);
	vec_add_apply(color, target);
	free(target);
}

static int				get_pixel_color(int *x, t_camera *cam, t_rt *rt)
{
	t_vec				*color;
	int					result;
	t_hitlst_info		*hinfo;

	color = vec_new(0, 0, 0);
	hinfo = get_hitlst_info(x[0], x[1], cam);
	get_hittable_color(rt->hitlst, hinfo, rt->lightlst, color);
	free_hitlst_info(hinfo, FALSE, FALSE);
	result = get_color_sample(color);
	free(color);
	return (result);
}

void					draw_hittable(t_camera *cam, t_rt *rt)
{
	int					x[2];

	x[1] = cam->data->height;
	while ((--x[1]) >= 0)
	{
		x[0] = -1;
		while ((++x[0]) < cam->data->width)
			cam->data->img[x[0]][x[1]] = get_pixel_color(x, cam, rt);
		ft_printf("Finish render line %d\n", x[1]);
	}
}
