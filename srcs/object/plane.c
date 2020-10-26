/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:05:47 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/26 21:59:02 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane		*plane_new(t_vec *dot, t_vec *normal)
{
	t_plane	*result;
	
	result = (t_plane *)malloc(sizeof(t_plane));
	result->dot = dot;
	result->normal = normal;

	return (result);
}

void		free_plane(t_plane *p)
{
	free(p->dot);
	free(p->normal);
	free(p);
}

int			is_in_plane(t_plane *p, t_vec *point)
{
	double	sum;
	int		i;

	sum = 0;
	i = -1;
	while ((++i) < 3)
		sum += (vec_idx(p->normal, i)
					* (vec_idx(point, i) - vec_idx(p->dot, i)));
	return (sum == 0 ? TRUE : FALSE);
}

double		get_plane_ray_t(t_plane *p, t_ray *r)
{
	double	tmp;

	tmp = vec_dot(p->normal, p->dot) - vec_dot(p->normal, r->orig);
	return (tmp / vec_dot(p->normal, r->dir));
}

int			plane_hit(void *plane, t_ray *r, t_hitlst_info *info,
							t_hit_record *rec)
{
	t_plane	*p;

	p = (t_plane *)plane;
	if (vec_is_orthogonal(r->dir, p->normal))
	{
		if (is_in_plane(p, r->orig) == FALSE)
			return (FALSE);
		rec->t = 0;
	}
	else
		rec->t = get_plane_ray_t(p, r);	
	rec->p = ray_at(r, rec->t);
	rec->normal = vec_unit(p->normal);
	hit_set_normal(rec, r);
	rec->mat = info->mat;
	return (TRUE);
}
