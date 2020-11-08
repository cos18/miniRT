/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 15:33:55 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/08 11:18:20 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere		*sphere_new(t_vec *center, double radius)
{
	t_sphere	*result;

	result = (t_sphere *)malloc_safe(sizeof(t_sphere));
	result->center = center;
	result->radius = radius;
	return (result);
}

void			free_sphere(t_sphere *s)
{
	free(s->center);
	free(s);
}

int				check_sphere_hitrange(void *s, t_ray *r,
									t_hitlst_info *info, t_hit_record *rec)
{
	int			is_big_t;
	double		t;

	is_big_t = -1;
	while ((++is_big_t) < 2)
	{
		t = (-info->half_b + info->root_d * (is_big_t ? (1) : (-1))) / info->a;
		if (info->t_min < t && t < info->t_max)
		{
			reset_hit_record(rec);
			rec->t = t;
			rec->p = ray_at(r, t);
			rec->normal = vec_sub(rec->p, ((t_sphere *)s)->center);
			vec_div_const_apply(rec->normal, ((t_sphere *)s)->radius);
			hit_set_normal(rec, r);
			rec->mat = material_dup(info->mat);
			rec->onum = info->onum;
			return (TRUE);
		}
	}
	return (FALSE);
}

int				sphere_hit(void *s, t_ray *r, t_hitlst_info *info,
							t_hit_record *rec)
{
	t_vec		*oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;

	oc = vec_sub(r->orig, ((t_sphere *)s)->center);
	a = vec_length_squared(r->dir);
	half_b = vec_dot(oc, r->dir);
	c = vec_length_squared(oc);
	c -= pow(((t_sphere *)s)->radius, 2);
	free(oc);
	discriminant = half_b * half_b - a * c;
	if (discriminant <= 0)
		return (FALSE);
	info->a = a;
	info->half_b = half_b;
	info->root_d = sqrt(discriminant);
	return (check_sphere_hitrange(s, r, info, rec));
}
