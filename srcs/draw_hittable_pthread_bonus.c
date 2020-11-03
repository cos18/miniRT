/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hittable_pthread_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 04:55:05 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/02 21:37:07 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
static t_vec		*get_sky_color_t(double t)
{
	t_vec			*target;
	t_vec			*tmp;

	tmp = vec_mul_const_apply(vec_create(0.5, 0.7, 1), t);
	target = vec_mul_const_apply(vec_create(1, 1, 1), 1.0 - t);
	vec_add_apply(target, tmp);
	free(tmp);
	return (target);
}
*/

static t_vec		*recur_anti_color(t_list *lst, t_hitlst_info **info,
											int depth, int *is_free)
{
	t_material		*mat;
	t_material_info	mat_info;
	t_vec			*target;
	double			t;

	if (depth <= 0 || hitlst_hit(lst, *info) == FALSE)
		return (vec_create(0, 0, 0));
	mat = (*info)->rec->mat;
	if ((t = (*(mat->scatter))(mat, (*info)->ray, (*info)->rec, &mat_info)))
	{
		if (mat->mat_type == MAT_LAMBERTIAN)
			target = vec_dup(mat_info.attenuation);
		else
		{
			free_hitlst_info(*info, (*is_free)++);
			*info = hitlst_info_new(mat_info.scattered);
			target = vec_mul_each_apply(
		recur_anti_color(lst, info, depth - 1, is_free), mat_info.attenuation);
		}
	}
	else
		target = vec_create(0, 0, 0);
	free_material_info(&mat_info, FALSE, !t);
	return (target);
}

static void			get_hittable_material_color(t_list *lst,
												t_hitlst_info *info,
												t_vec *color)
{
	t_vec			*target;
	int				is_free;

	is_free = FALSE;
	target = recur_anti_color(lst, &info, REFLECT_DEPTH, &is_free);
	vec_add_apply(color, target);
	free(target);
	free_hitlst_info(info, is_free);
}

static void			*render(void *arg)
{
	int				x;
	int				y;
	int				locate;
	t_vec			*color;
	t_thread_info	*tinfo;

	tinfo = (t_thread_info *)arg;
	y = tinfo_get_y_init_value(tinfo);
	while ((--y) >= (tinfo_get_step(tinfo) * (tinfo->tnum - 1)))
	{
		x = -1;
		while ((++x) < tinfo->cam->data->width)
		{
			color = vec_create(0, 0, 0);
			locate = -1;
			while ((++locate) < ANTI_SAMPLES)
				get_hittable_material_color(tinfo->lst,
								get_hitlst_info_anti(x, y, tinfo->cam), color);
			tinfo->cam->data->img[x][y] = get_color_sample_gamma(color);
			free(color);
		}
		ft_printf("Finish render line %d\n", y);
	}
	free(tinfo);
	return (NULL);
}

void				draw_hittable_pthread(t_camera *cam, t_list *lst)
{
	pthread_t		*threads;
	int				pnum;
	t_thread_info	*info;

	threads = (pthread_t *)malloc_safe(sizeof(pthread_t) * PTHREAD_CNT);
	pnum = 0;
	while (++pnum <= PTHREAD_CNT)
	{
		info = tinfo_new(cam, lst, pnum);
		pthread_create(&(threads[pnum - 1]), NULL, render, (void *)info);
	}
	pnum = 0;
	while (++pnum <= PTHREAD_CNT)
		pthread_join(threads[pnum - 1], NULL);
	free(threads);
}
