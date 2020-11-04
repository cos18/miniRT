/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@studne>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:05:47 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/04 20:24:25 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder		*cylinder_new(t_vec *start_vec, t_vec *normal,
								double radius, double height)
{
	t_cylinder	*result;
	
	result = (t_cylinder *)malloc_safe(sizeof(t_cylinder));
	result->start = ray_new(start_vec, normal);
	result->radius = radius;
	result->end_t = height / vec_length(result->start->dir);
	return (result);
}

void			free_cylinder(t_cylinder *cy)
{
	free_ray(cy->start, TRUE);
	free(cy);
}

int				cylinder_hit(void *cylinder, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec)
{
	t_cylinder	*cy;
	
	cy = (t_cylinder *)cylinder;
	if (vec_is_orthogonal(r->dir, p->normal))
		return (FALSE);
	t = get_plane_ray_t(p, r);
	if (info->t_min >= t || t >= info->t_max)
		return (FALSE);
	reset_hit_record(rec);
	rec->t = t;
	rec->p = ray_at(r, rec->t);
	rec->normal = vec_unit(p->normal);
	hit_set_normal(rec, r);
	rec->mat = info->mat;
	return (TRUE);
}
