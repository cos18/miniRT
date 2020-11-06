/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:05:46 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:24:55 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double				random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double				random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

t_hitlst_info		*get_hitlst_info_anti(int x, int y, t_camera *cam)
{
	double			u;
	double			v;
	t_ray			*ray;

	u = ((double)x + random_double()) / (cam->data->width - 1);
	v = ((double)y + random_double()) / (cam->data->height - 1);
	ray = camera_get_ray(cam, u, v);
	return (hitlst_info_new(ray, INFINITY));
}
