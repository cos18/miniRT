/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hittable_pthread_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 04:55:05 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/10 23:11:31 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void				get_hittable_material_color(t_list *hitlst,
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
		linfo = lhit_info_new(info->rec->p, info->rec->normal, info->ray,
								info->rec->onum);
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

static int				get_pixel_color(int *x, t_thread_info *tinfo)
{
	t_vec				*color;
	int					result;
	int					locate;
	t_hitlst_info		*hinfo;

	color = vec_new(0, 0, 0);
	locate = -1;
	while ((++locate) < ANTI_SAMPLES)
	{
		hinfo = get_hitlst_info_anti(x[0], x[1], tinfo->cam);
		get_hittable_material_color(tinfo->hitlst, hinfo, tinfo->lightlst,
										color);
		free_hitlst_info(hinfo, FALSE, FALSE);
	}
	result = get_color_sample_gamma(color);
	free(color);
	return (result);
}

static void				*render(void *arg)
{
	int					x[2];
	t_thread_info		*tinfo;

	tinfo = (t_thread_info *)arg;
	x[1] = tinfo_get_y_init_value(tinfo);
	while ((--x[1]) >= (tinfo_get_step(tinfo) * (tinfo->tnum - 1)))
	{
		x[0] = -1;
		while ((++x[0]) < tinfo->cam->data->width)
			tinfo->cam->data->img[x[0]][x[1]] = get_pixel_color(x, tinfo);
		ft_printf("Finish render line %d in Thread %d\n", x[1], tinfo->tnum);
	}
	free(tinfo);
	return (NULL);
}

void					draw_hittable_pthread(t_camera *cam, t_rt *rt)
{
	pthread_t			*threads;
	int					pnum;
	t_thread_info		*info;

	threads = (pthread_t *)malloc_safe(sizeof(pthread_t) * PTHREAD_CNT);
	pnum = 0;
	ft_printf("Start Rendering with %d Threads!\n", PTHREAD_CNT);
	while (++pnum <= PTHREAD_CNT)
	{
		info = tinfo_new(cam, rt, pnum);
		pthread_create(&(threads[pnum - 1]), NULL, render, (void *)info);
	}
	pnum = 0;
	while (++pnum <= PTHREAD_CNT)
		pthread_join(threads[pnum - 1], NULL);
	free(threads);
}
