/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:01:26 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/10 20:38:26 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double			g_t;

static int		cylinder_get_abc(t_cylinder *cy, t_ray *r, t_hitlst_info *info)
{
	t_vec		*delta_p;
	t_vec		*tmp;
	t_vec		*tmp2;
	double		discriminant;

	tmp = vec_mul_c(cy->start->dir, vec_dot(cy->start->dir, r->dir));
	info->a = vec_length_squared(vec_sub_apply(tmp, r->dir));
	delta_p = vec_sub(r->orig, cy->start->dir);
	tmp2 = vec_mul_c(cy->start->dir, vec_dot(cy->start->dir, delta_p));
	info->half_b = vec_dot(tmp, vec_sub_apply(tmp2, delta_p));
	info->c = vec_length_squared(tmp2) - pow(cy->radius, 2.0);
	discriminant = info->half_b * info->half_b - info->a * info->c;
	free(delta_p);
	free(tmp);
	free(tmp2);
	if (discriminant <= 0)
		return (FALSE);
	info->root_d = sqrt(discriminant);
	return (TRUE);
}

static int		cylinder_check_height(t_cylinder *cy, t_ray *r)
{
	t_vec		*tmp_p;
	t_vec		*tmp;
	double		dot;
	int			result;

	tmp_p = ray_at(r, g_t);
	tmp = vec_sub(tmp_p, cy->start->orig);
	dot = vec_dot(cy->start->dir, tmp);
	free(tmp);
	result = (dot > 0) ? TRUE : FALSE;
	tmp = vec_sub(tmp_p, cy->end_p);
	dot = vec_dot(cy->start->dir, tmp);
	free(tmp);
	result = ((dot < 0) && result) ? TRUE : FALSE;
	free(tmp_p);
	return (result);
}

static int		cylinder_set_rec(t_cylinder *cy, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec)
{
	t_vec		*tmp;
	double		dot;

	reset_hit_record(rec);
	rec->t = g_t;
	rec->p = ray_at(r, g_t);
	tmp = vec_sub(rec->p, cy->start->orig);
	dot = vec_dot(cy->start->dir, tmp) / vec_length(cy->start->dir);
	rec->normal = vec_sub_apply(vec_mul_c(cy->start->dir, dot), tmp);
	free(tmp);
	vec_unit_apply(rec->normal);
	hit_set_normal(rec, r);
	rec->mat = material_dup(info->mat);
	rec->onum = info->onum;
	return (TRUE);
}

int				cylinder_hit(void *cylinder, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec)
{
	t_cylinder	*cy;
	int			is_big_t;

	cy = (t_cylinder *)cylinder;
	if (cylinder_get_abc(cy, r, info) == FALSE)
		return (FALSE);
	is_big_t = -1;
	while ((++is_big_t) < 2)
	{
		g_t = (-info->half_b + info->root_d * (is_big_t ? (1) : (-1)))
				/ info->a;
		if (info->t_min < g_t && g_t < info->t_max)
		{
			if (cylinder_check_height(cy, r))
				return (cylinder_set_rec(cy, r, info, rec));
		}
	}
	return (FALSE);
}
