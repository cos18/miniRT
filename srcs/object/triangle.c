/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:27:37 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:58:47 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_triangle		*triangle_new(t_vec *a, t_vec *b, t_vec *c)
{
	t_triangle	*result;

	result = (t_triangle *)malloc_safe(sizeof(t_triangle));
	result->a = a;
	result->b = b;
	result->c = c;
	result->side_a = vec_sub(b, a);
	result->side_b = vec_sub(c, a);
	result->side_c = vec_sub(c, b);
	result->normal = vec_unit_apply(vec_cross(result->side_a, result->side_b));
	return (result);
}

void			free_triangle(t_triangle *tr)
{
	free(tr->a);
	free(tr->b);
	free(tr->c);
	free(tr->normal);
	free(tr->side_a);
	free(tr->side_b);
	free(tr->side_c);
	free(tr);
}

static int		triangle_is_in(t_triangle *tr, t_vec *p)
{
	t_vec		*tmp;
	double		dot;

	tmp = vec_sub(p, tr->a);
	dot = vec_dot(vec_cross_apply_tob(tr->side_a, tmp), tr->normal);
	free(tmp);
	if (dot < 0)
		return (FALSE);
	tmp = vec_sub(p, tr->a);
	dot = vec_dot(vec_cross_apply(tmp, tr->side_b), tr->normal);
	free(tmp);
	if (dot < 0)
		return (FALSE);
	tmp = vec_sub(p, tr->b);
	dot = vec_dot(vec_cross_apply_tob(tr->side_c, tmp), tr->normal);
	free(tmp);
	return ((dot >= 0) ? TRUE : FALSE);
}

int				triangle_hit(void *triangle, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec)
{
	t_triangle	*tr;
	double		t;
	t_vec		*tmp_p;

	tr = (t_triangle *)triangle;
	if (vec_is_orthogonal(r->dir, tr->normal))
		return (FALSE);
	t = get_plane_ray_t(tr->a, tr->normal, r);
	if (info->t_min >= t || t >= info->t_max)
		return (FALSE);
	tmp_p = ray_at(r, t);
	if (triangle_is_in(tr, tmp_p) == FALSE)
	{
		free(tmp_p);
		return (FALSE);
	}
	reset_hit_record(rec);
	rec->t = t;
	rec->p = tmp_p;
	rec->normal = vec_dup(tr->normal);
	hit_set_normal(rec, r);
	rec->mat = material_dup(info->mat);
	return (TRUE);
}
