/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:28:05 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/10 20:38:47 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec		*vec_add(t_vec *a, t_vec *b)
{
	t_vec	*result;

	result = (t_vec*)malloc_safe(sizeof(t_vec));
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
	return (result);
}

t_vec		*vec_sub(t_vec *a, t_vec *b)
{
	t_vec	*result;

	result = (t_vec*)malloc_safe(sizeof(t_vec));
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
	return (result);
}

t_vec		*vec_mul_c(t_vec *a, double c)
{
	t_vec	*result;

	result = (t_vec*)malloc_safe(sizeof(t_vec));
	result->x = a->x * c;
	result->y = a->y * c;
	result->z = a->z * c;
	return (result);
}

t_vec		*vec_div_c(t_vec *a, double c)
{
	t_vec	*result;

	result = (t_vec*)malloc_safe(sizeof(t_vec));
	result->x = a->x / c;
	result->y = a->y / c;
	result->z = a->z / c;
	return (result);
}

t_vec		*vec_reflect(t_vec *v, t_vec *n)
{
	t_vec	*result;
	t_vec	*tmp;

	tmp = vec_mul_c(n, 2 * vec_dot(v, n));
	result = vec_sub(v, tmp);
	free(tmp);
	return (result);
}
