/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitlst_info_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 04:25:55 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:30:46 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitlst_info		*hitlst_info_new(t_ray *r, double tmax)
{
	t_hitlst_info	*result;

	result = (t_hitlst_info *)malloc_safe(sizeof(t_hitlst_info));
	result->ray = r;
	result->t_min = HIT_T_MIN;
	result->t_max = tmax;
	result->rec = hit_record_new();
	result->mat = NULL;
	return (result);
}

t_hitlst_info		*get_hitlst_info(int x, int y, t_camera *cam)
{
	double			u;
	double			v;
	t_ray			*ray;

	u = ((double)x) / (cam->data->width - 1);
	v = ((double)y) / (cam->data->height - 1);
	ray = camera_get_ray(cam, u, v);
	return (hitlst_info_new(ray, INFINITY));
}

void				free_hitlst_info(t_hitlst_info *info, int is_ray_ori_free,
										int is_mat_free)
{
	if (is_mat_free && info->mat)
		free_material(info->mat);
	free_ray(info->ray, is_ray_ori_free);
	free_hit_record(info->rec);
	free(info);
}
