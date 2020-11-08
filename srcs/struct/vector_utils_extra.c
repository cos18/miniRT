/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:54:02 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/08 15:13:32 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			vec_is_parallel(t_vec *a, t_vec *b)
{
	double	dot;
	double	length;

	dot = vec_dot(a, b);
	dot = ((dot < 0) ? (-1 * dot) : dot);
	length = vec_length(a) * vec_length(b);
	return ((dot == length) ? TRUE : FALSE);
}

int			vec_is_orthogonal(t_vec *a, t_vec *b)
{
	return (vec_dot(a, b) == 0 ? TRUE : FALSE);
}

double		vec_idx(t_vec *a, int idx)
{
	if (idx == 0)
		return (a->x);
	if (idx == 1)
		return (a->y);
	if (idx == 2)
		return (a->z);
	return (INFINITY);
}

int			vec_is_color_range(t_vec *a)
{
	if (a->x < 0 || 255 < a->x)
		return (FALSE);
	if (a->y < 0 || 255 < a->y)
		return (FALSE);
	if (a->z < 0 || 255 < a->z)
		return (FALSE);
	return (TRUE);
}
