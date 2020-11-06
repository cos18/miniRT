/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:05:47 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:23:27 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder		*cylinder_new(t_vec *start_vec, t_vec *normal,
								double radius, double height)
{
	t_cylinder	*result;
	double		end_t;

	result = (t_cylinder *)malloc_safe(sizeof(t_cylinder));
	result->start = ray_new(start_vec, normal);
	result->radius = radius;
	end_t = height / vec_length(result->start->dir);
	result->end_p = ray_at(result->start, end_t);
	return (result);
}

void			free_cylinder(t_cylinder *cy)
{
	free_ray(cy->start, TRUE);
	free(cy->end_p);
	free(cy);
}
