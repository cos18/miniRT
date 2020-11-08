/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:16:51 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/08 10:49:05 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	*find_ab_center(t_square *sq, t_vec *c, double xy_c)
{
	double		coef[4];
	double		x;

	coef[0] = -1 * sq->normal->x / sq->normal->y;
	coef[1] = c->y - coef[0] * c->x
				+ sq->normal->z * (c->z - xy_c) / sq->normal->y;
	coef[2] = sq->normal->y / sq->normal->x;
	coef[3] = c->y - coef[2] * c->x;
	x = (coef[3] - coef[1]) / (coef[0] - coef[2]);
	return (vec_new(x, coef[0] * x + coef[1], xy_c));
}

static void		square_set_abcd_final(t_square *sq, t_vec *c, t_vec *ab_center)
{
	t_vec		*cross_n;
	t_vec		*up;

	cross_n = vec_unit_apply(vec_new(sq->normal->y, -1 * sq->normal->x, 0));
	sq->b = vec_add_apply(vec_mul_const(cross_n, sq->h_side), ab_center);
	sq->a = vec_add_apply(vec_mul_const(cross_n, -1 * sq->h_side), ab_center);
	up = vec_sub(c, ab_center);
	sq->c = vec_add_apply(vec_mul_const(up, 2), sq->b);
	sq->d = vec_add_apply(vec_mul_const(up, 2), sq->a);
	free(up);
	free(cross_n);
}

static void		square_set_abcd(t_square *sq, t_vec *c)
{
	double		xy_c;
	t_vec		*ab_center;

	xy_c = c->z - sq->h_side * sqrt(1 - pow(sq->normal->z, 2));
	if (sq->normal->x == 0)
	{
		ab_center = vec_new(c->x, c->y + sq->h_side * sq->normal->z, xy_c);
		if (is_in_plane(c, sq->normal, ab_center) == FALSE)
			ab_center->y = c->y - sq->h_side * sq->normal->z;
	}
	else if (sq->normal->y == 0)
	{
		ab_center = vec_new(c->x + sq->h_side * sq->normal->z, c->y, xy_c);
		if (is_in_plane(c, sq->normal, ab_center) == FALSE)
			ab_center->x = c->x + sq->h_side * sq->normal->z;
	}
	else
		ab_center = find_ab_center(sq, c, xy_c);
	square_set_abcd_final(sq, c, ab_center);
	free(ab_center);
}

t_square		*square_new(t_vec *c, t_vec *normal, double side)
{
	t_square	*result;

	result = (t_square *)malloc_safe(sizeof(t_square));
	result->normal = vec_unit_apply(normal);
	result->h_side = side / 2.0;
	if (normal->x == 0 && normal->y == 0)
	{
		result->a = vec_add_apply(vec_new(-1 * c->x, -1 * c->y, 0), c);
		result->b = vec_add_apply(vec_new(c->x, -1 * c->y, 0), c);
		result->c = vec_add_apply(vec_new(c->x, c->y, 0), c);
		result->d = vec_add_apply(vec_new(-1 * c->x, c->y, 0), c);
	}
	else
		square_set_abcd(result, c);
	return (result);
}

void			free_square(t_square *sq)
{
	free(sq->normal);
	free(sq->a);
	free(sq->b);
	free(sq->c);
	free(sq->d);
	free(sq);
}
