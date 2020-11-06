/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:31:49 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 22:21:48 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		square_check_in(t_square *sq, t_vec *tmp_p)
{
	t_vec		*a_p;
	t_vec		*tmp;
	double		dot;

	a_p = vec_sub(tmp_p, sq->a);
	tmp = vec_sub(sq->b, sq->a);
	dot = vec_dot(a_p, tmp);
	free(tmp);
	if (dot < 0 || dot > pow(2 * sq->h_side, 2))
	{
		free(a_p);
		return (FALSE);
	}
	tmp = vec_sub(sq->d, sq->a);
	dot = vec_dot(a_p, tmp);
	free(tmp);
	free(a_p);
	return ((0 <= dot && dot <= pow(2 * sq->h_side, 2)) ? TRUE : FALSE);
}

int				square_hit(void *square, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec)
{
	t_square	*sq;
	double		t;
	t_vec		*tmp_p;

	sq = (t_square *)square;
	if (vec_is_orthogonal(r->dir, sq->normal))
		return (FALSE);
	t = get_plane_ray_t(sq->a, sq->normal, r);
	tmp_p = ray_at(r, t);
	if (square_check_in(sq, tmp_p) == FALSE)
	{
		free(tmp_p);
		return (FALSE);
	}
	reset_hit_record(rec);
	rec->t = t;
	rec->p = tmp_p;
	rec->normal = vec_dup(sq->normal);
	hit_set_normal(rec, r);
	vec_mul_const_apply(rec->normal, -1);
	rec->mat = material_dup(info->mat);
	return (TRUE);
}
